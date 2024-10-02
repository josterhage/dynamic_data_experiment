#include <errno.h>
#include <stdlib.h>

#include "alloc.h"
#include "tests.h"

struct ll_test_manager {
	struct test_manager base;
	struct list_head test_list;
	struct test_struct *test_data;
};

static inline size_t get_mempool_size(struct ll_test_manager *manager)
{
	return (((manager->base.word_list_size / LINES) * manager->test_data->elements)
	       + (manager->test_data->elements * sizeof(struct ll_struct)) + 4096)
		   & (UINTPTR_MAX - 0xFFF);
}

static int ll_create_test(struct test_manager *manager,
										  struct mm_struct *allocator)
{
	struct ll_test_manager *ll_mgr = manager;
	return NULL;
}

static int ll_read_test(struct test_manager *manager,
										struct mm_struct *allocator)
{
	struct ll_test_manager *ll_mgr = manager;
	return NULL;
}

static int ll_update_test(struct test_manager *manager,
										  struct mm_struct *allocator)
{
	struct ll_test_manager *ll_mgr = manager;
	return NULL;
}

static int ll_delete_test(struct test_manager *manager,
										  struct mm_struct *allocator)
{
	struct ll_test_manager *ll_mgr = manager;
	return NULL;
}

static int do_ll_tests(struct test_manager *manager, struct test_struct *ts)
{
	struct ll_test_manager *ll_mgr = manager;
	ll_mgr->test_data = ts;

	struct mm_struct *allocator = NULL;

	switch (ts->method) {
		case STDLIB:
			allocator = get_allocator(get_mempool_size(ll_mgr), sizeof(struct ll_struct));
			break;
		case MEMPOOL:
			allocator = get_allocator(0, sizeof(struct ll_struct));
	}

	if (!allocator) {
		errno = ENOMEM;
		return -1;
	}

	for (int i = 0; i < ts->iterations; i++) {
		// create the list
		struct test_result *res = calloc(1, sizeof(struct test_result));
		res->method = ts->method;
		res->structure = LINKED_LIST;
		res->operation = CREATE;
		res->runtime_hz = manager->do_one_test(manager, ll_create_test);
		list_add(&res->list_node, &manager->results);

		// do the read test
		res = calloc(1, sizeof(struct test_result));
		res->method = ts->method;
		res->structure = LINKED_LIST;
		res->operation = READ;
		res->runtime_hz = manager->do_one_test(manager, ll_read_test);
		list_add(&res->list_node, &manager->results);

		//do the update test
		res = calloc(1, sizeof(struct test_result));
		res->method = ts->method;
		res->structure = LINKED_LIST;
		res->operation = UPDATE;
		res->runtime_hz = manager->do_one_test(manager, ll_update_test);
		
		//do the delete test
		res = calloc(1, sizeof(struct test_result));
		res->method = ts->method;
		res->structure = LINKED_LIST;
		res->operation = DELETE;
		res->runtime_hz = manager->do_one_test(manager, ll_delete_test);

		// clear the test data
	}
	return 0;
}

struct test_manager *init_ll_test_manager(void)
{
	struct ll_test_manager *new = calloc(1, sizeof(struct ll_test_manager));
	init_manager(&new->base);
	INIT_LIST_HEAD(&new->test_list);
}