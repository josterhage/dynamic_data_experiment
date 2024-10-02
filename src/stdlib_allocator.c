#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "alloc.h"

struct stdlib_priv {
	size_t object_size;
};

static void *stdlib_malloc(struct mm_struct *mm_struct)
{
	struct stdlib_priv *priv = mm_struct->mm_priv;
	return malloc(priv->object_size);
}

static void *stdlib_calloc(struct mm_struct *mm_struct)
{
	void *ptr = stdlib_malloc(mm_struct);
	struct stdlib_priv *priv = mm_struct->mm_priv;

	memset(ptr, 0, priv->object_size);

	return ptr;
}

static void stdlib_free(struct mm_struct *mm_struct, void *obj)
{
	free(obj);
}

struct mm_struct *get_stdlib_allocator(size_t size, size_t object_size)
{
	struct mm_struct *new = calloc(1, sizeof(struct mm_struct));
	struct stdlib_priv *priv = calloc(1, sizeof(struct stdlib_priv));
	new->malloc = stdlib_malloc;
	new->calloc = stdlib_calloc;
	new->free = stdlib_free;
	priv->object_size = object_size;
	new->mm_priv = priv;
	return new;
}

void delete_stdlib_allocator(struct mm_struct *allocator)
{
	free(allocator->mm_priv);
	free(allocator);
}