#ifndef ALLOC_H
#define ALLOC_H

#include <stddef.h>

struct mm_struct {
	void *(*malloc)(struct mm_struct *mm_struct);
	void *(*calloc)(struct mm_struct *mm_struct);
	void (*free)(struct mm_struct *mm_struct, void *obj);
	void *mm_priv;
};

struct mm_struct *get_allocator(size_t size, size_t object_size);
void delete_allocator(struct mm_struct *allocator);

struct mm_struct *get_stdlib_allocator(size_t size, size_t object_size);
void delete_stdlib_allocator(struct mm_struct *allocator);

#endif /* ALLOC_H */