#ifndef TESTS_H
#define TESTS_H

#include <stdint.h>
#include <time.h>

#include "linux-list.h"

#define LINES 466550 // output from wc -l words.txt

enum data_structure {
	LINKED_LIST,
	DYNAMIC_ARRAY,
};

enum allocation_method {
	STDLIB,
	MEMPOOL,
};

enum operation {
	CREATE,
	READ,
	UPDATE,
	DELETE,
};

extern const char *data_structure_names[];
extern const char *allocation_method_names[];
extern const char *operation_names[];

struct test_result {
	enum data_structure 	structure;
	enum allocation_method 	method;
	enum operation			operation;
	uint64_t				runtime_hz;
	struct list_head		list_node;
};

struct test_manager;

typedef int (*test_fn)(struct test_manager *, struct mm_struct *);

struct test_struct {
	enum allocation_method method;
	size_t elements;
	size_t iterations;
};

struct test_manager {
	char **word_list;
	size_t word_list_size;
	int common_index[LINES];
	struct timespec ts;
	struct list_head results;
	void (*add_result)(struct test_manager *, struct test_result *);
	void (*print_results)(struct test_manager *);
	int (*save_results)(struct test_manager *, char *path);
	void (*close_base_manager)(struct test_manager *);
	uint64_t (*do_one_test)(struct test_manager *, test_fn fn);
	/* Pure virtual */
	int (*do_tests)(struct test_manager *, struct test_struct *);
};

void init_manager(struct test_manager *new);
void randomize_index(struct timespec *ts, int *index, int n);

struct test_manager *init_ll_test_manager(void);


struct ll_struct {
	char *name;
	int name_len;
	int major;
	int minor;
	void *priv;
	struct list_head list;
};

struct arr_struct {
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