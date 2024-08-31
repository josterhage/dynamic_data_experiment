#ifndef TESTS_H
#define TESTS_H

#include <stdint.h>
#include <time.h>

#include "linux-list.h"

#define LINES 466550 // output from wc -l words.txt
#define WORDS_MEM_SZ LINES * sizeof(size_t)

struct test_manager {
	char **word_list;
	int common_index[LINES];
	struct timespec ts;
	struct list_head results;
};

enum data_structure {
	LINKED_LIST,
	DYNAMIC_ARRAY,
};

enum allocation_method {
	STDLIB,
	MEMPOOL,
};

enum operation {
	CREATE = 1,
	READ   = 2,
	UPDATE = 4,
	DELETE = 8,
};

extern const char *data_structure_names[];
extern const char *allocation_method_names[];
extern const char *operation_names[];

struct test_result {
	enum data_structure 	structure;
	enum allocation_method 	method;
	enum operation			ops;
	int 					nr_ops;
	uint64_t				tsc_start;
	uint64_t				tsc_end;
	struct list_head		list_node;
};

struct mm_struct {
	void *(*alloc)(struct mm_struct *mm_struct, size_t size);
	void (*free)(struct mm_struct *mm_struct, void *obj);
	void *mm_priv;
};

struct mm_struct *get_mempool_allocator(size_t size, size_t object_size);
void delete_mempool_allocator(struct mm_struct *allocator);

void load_words(void);
void close_all(void);
void do_test_a(int count);
void do_test_b(int count);

struct struct_a {
	char *name;
	int name_len;
	int major;
	int minor;
	void *priv;
	struct list_head list;
};

struct struct_b {
	char *name;
	int name_len;
	int major;
	int minor;
	void *priv;
};

struct priv {
	int a;
	int b;
	int c;
};

static inline volatile uint64_t get_tsc(void)
{
	uint64_t ret;

	asm volatile ("mfence\n\t"
				  "lfence\n\t"
				  "rdtsc\n\t"
				  "lfence\n\t"
				  "shlq $32, %%rdx\n\t"
				  "orq  %%rdx, %0\n\t "
				  : "=r" (ret)
				  :
				  : "rdx");
    return ret;
}

#endif /* TESTS_H */