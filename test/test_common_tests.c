#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tests.h"

static LIST_HEAD(test_list);

static int test_fn_test(struct test_manager *manager)
{
	/* 100 item linked-list build */
	int index[100];
	randomize_index(&manager->ts, manager->common_index, LINES);
	memcpy(index, manager->common_index, 100 * sizeof(int));
	for (size_t i = 0; i < 100; i++) {
		struct struct_a *new = calloc(1, sizeof(struct struct_a));
		new->name_len = strlen(manager->word_list[index[i]]) + 1;
		new->name = calloc(new->name_len, sizeof(char));
		snprintf(new->name, new->name_len, "%s", manager->word_list[index[i]]);
		new->major = rand();
		new->minor = rand();
		new->priv = calloc(1, sizeof(struct priv));
		struct priv *priv = new->priv;
		priv->a = rand();
		priv->b = rand();
		priv->c = rand();

		list_add(&new->list, &test_list);
	}
	return 0;
}

static void do_tests(struct test_manager *manager, enum allocation_method method, 
					 enum operation operation, int count)
{
	for (int i = 0; i < count; i++) {
		struct test_result *result = 
			manager->do_one_test(manager, LINKED_LIST, STDLIB, CREATE, test_fn_test);
		if (result) {
			manager->add_result(manager, result);
		}
	}
}

int main(void)
{
	struct test_manager *manager = calloc(1, sizeof(struct test_manager));

	init_manager(manager);

	if (!manager) {
		printf("Failed to allocate test manager, aborting\n");
		exit(EXIT_FAILURE);
	}
	printf("Successfully constructed test manager\n");

	if (!manager->word_list) {
		printf("Failed to create word list, aborting\n");
		exit(EXIT_FAILURE);
	}
	printf("Successfully constructed word list\n");

	if (!manager->ts.tv_nsec || !manager->ts.tv_sec) {
		printf("Failed to initialize clock, aborting\n");
		exit(EXIT_FAILURE);
	}
	printf("Successfully initialized clock\n");

	manager->do_tests = do_tests;

	manager->do_tests(manager, STDLIB, CREATE, 20);

	manager->save_results(manager, "/home/james/test2.csv");

	struct struct_a *a_del, *a_tmp;
	list_for_each_entry_safe(a_del, a_tmp, &test_list, list) {
		list_del(&a_del->list);
		free(a_del->name);
		free(a_del->priv);
		free(a_del);
	}

	struct test_result *res_del, *res_tmp;
	list_for_each_entry_safe(res_del, res_tmp, &manager->results, list_node) {
		list_del(&res_del->list_node);
		free(res_del);
	}
}