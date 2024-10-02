#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "alloc.h"
#include "linux-list.h"
#include "tests.h"

#ifdef MEMPOOL_DEBUG
#include <stdio.h>
#define DPRINTF(fmt, ...) \
	printf(__FILE__##fmt, ##__VA_ARGS__)
#else
#define DPRINTF(fmt,...)
#endif

#define MAX_OBJS(psz, osz) ((psz) / (QWORD_ALIGN(osz)))

#define PAGE_ALIGN(sz)		(((sz) + 0xfff) & ~0xfff)

#define QWORD_ALIGN(sz)		(((sz) + 7) & ~7)

#define _POOL_OVERHEAD(ct) \
	QWORD_ALIGN(sizeof(struct mm_struct)) + \
	(QWORD_ALIGN(sizeof(struct mem_node)) * ct ) 

#define POOL_OVERHEAD(ct) \
	PAGE_ALIGN(_POOL_OVERHEAD(ct))

struct mem_node {
	void *ptr;
	struct list_head list;
};

struct mm_priv {
	void *pool;
	size_t allocator_size;
	size_t pool_size;
	size_t object_size;
	size_t max_objs;
	struct list_head free_list;
	struct list_head used_list;
};

static void init_chunk_lists(struct mm_priv *mm)
{
	INIT_LIST_HEAD(&mm->free_list);
	INIT_LIST_HEAD(&mm->used_list);
	void *first_node = ((void *)mm) + QWORD_ALIGN(sizeof(struct mm_priv));
	for ( size_t i = 0; i < mm->max_objs; i++ ) {
		struct mem_node *next_node = first_node + (i * QWORD_ALIGN(sizeof(struct mem_node)));
		next_node->ptr = mm->pool + (i * QWORD_ALIGN(mm->object_size));
		list_add(&next_node->list, &mm->free_list);
	}
}

static void *mempool_malloc(struct mm_struct *mm_struct)
{
	struct mm_priv *priv = mm_struct->mm_priv;
	if ( list_empty(&priv->free_list) ) {
		return NULL;
	}

	struct mem_node *node = list_entry(priv->free_list.next, struct mem_node, list);
	list_del(&node->list);
	list_add(&node->list, &priv->used_list);

	return node->ptr;
}

static void *mempool_calloc(struct mm_struct *mm_struct)
{
	void *obj = mempool_malloc(mm_struct);
	struct mm_priv *priv = mm_struct->mm_priv;
	for ( size_t i = 0; i < (priv->object_size / 8); i++ ) {
		*(unsigned long *)(obj + i) = 0;
	}
	return obj;
}

static void mempool_free(struct mm_struct *mm_struct, void *obj)
{
	struct mm_priv *priv = mm_struct->mm_priv;

	struct mem_node *node;
	list_for_each_entry(node, &priv->used_list, list)
	{
		if ( node->ptr == obj ) {
			break;
		}
	}
	list_del(&node->list);

	list_add(&node->list, &priv->free_list);
}

static struct mm_struct *get_mempool_allocator(size_t pool_size, size_t object_size)
{
	size_t objs = MAX_OBJS(pool_size, object_size);
	size_t allocator_size = POOL_OVERHEAD(objs);
	struct mm_struct *allocator = mmap(NULL, allocator_size, PROT_READ | PROT_WRITE,
									   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if ( !allocator ) {
		return NULL;
	}
	DPRINTF("mmap for allocator successful. Allocation at address %p\n", allocator);
	allocator->mm_priv = allocator + QWORD_ALIGN(sizeof(struct mm_struct));
	allocator->malloc = mempool_malloc;
	allocator->calloc = mempool_calloc;
	allocator->free = mempool_free;

	struct mm_priv *priv = allocator->mm_priv;
	priv->allocator_size = allocator_size;
	priv->pool_size = PAGE_ALIGN(pool_size);
	priv->pool = mmap(NULL, priv->pool_size, PROT_READ | PROT_WRITE,
					  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	DPRINTF("mmap for pool successful. Allocation at address %p\n", priv->pool);
	priv->object_size = object_size;
	priv->max_objs = objs;
	init_chunk_lists(priv);

	return allocator;
}

static void delete_mempool_allocator(struct mm_struct *allocator)
{
	struct mm_priv *priv = allocator->mm_priv;
	size_t allocator_size = priv->allocator_size;
	munmap(priv->pool, priv->pool_size);
	munmap(allocator, allocator_size);
}

struct mm_struct *get_allocator(size_t pool_size, size_t object_size)
{
	return get_mempool_allocator(pool_size, object_size);
}

void delete_allocator(struct mm_struct *allocator)
{
	delete_mempool_allocator(allocator);
}