#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "linux-list.h"
#include "tests.h"

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
	for (size_t i = 0; i < mm->max_objs; i++) {
		struct mem_node *next_node = first_node + (i * QWORD_ALIGN(sizeof(struct mem_node)));
		next_node->ptr = mm->pool + (i * QWORD_ALIGN(mm->object_size));
		list_add(&next_node->list, &mm->free_list);
	}
}

struct mm_struct *get_mempool_allocator(size_t pool_size, size_t object_size)
{
	size_t objs = MAX_OBJS(pool_size, object_size);
	struct mm_struct *allocator = mmap(NULL, POOL_OVERHEAD(objs), PROT_READ | PROT_WRITE,
	                                	MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	allocator->mm_priv = allocator + QWORD_ALIGN(sizeof(struct mm_struct));
	struct mm_priv *priv = allocator->mm_priv;
	priv->pool_size = PAGE_ALIGN(pool_size);
	priv->pool = mmap(NULL, priv->pool_size, PROT_READ | PROT_WRITE,
						MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	priv->object_size = object_size;
	priv->max_objs = objs;
	init_chunk_lists(priv);
	
	
	return allocator;
}