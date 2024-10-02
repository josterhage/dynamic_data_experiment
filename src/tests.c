#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>


#include "linux-list.h"
#include "tests.h"

static LIST_HEAD(struct_a_list);

static struct struct_a *new_struct_a(char *name)
{
	struct timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	struct struct_a *_new = calloc(1, sizeof(struct struct_a));
	srand(ts.tv_nsec);

	_new->name_len = strlen(name) + 1;
	_new->name = calloc(_new->name_len, sizeof(char));
	strcpy(_new->name, name);
	_new->major = rand();
	_new->minor = rand();
	_new->priv = calloc(1, sizeof(struct priv));

	return _new;
}

static void free_list(void) {
	struct list_head *cursor;
	struct list_head *tmp;
	list_for_each_safe(cursor, tmp, &struct_a_list){
		list_del(cursor);
		free(list_entry(cursor,struct struct_a, list));
	}
}

static void set_priv(void *priv) {
	struct priv *_priv = priv;

	struct timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	srand(ts.tv_nsec);

	_priv->a = rand();
	_priv->b = rand();
	_priv->c = rand();
}

void do_test_a(int count)
{
	int set_list[count];
	int get_list[count];
	randomize_index(all_index, LINES);

	memcpy(set_list, all_index, count * sizeof(int));
	memcpy(get_list, set_list, count * sizeof(int));

	randomize_index(get_list, count);

	printf("Test 1: Filling a linked-list with %d instances of struct_a\n", count);

	uint64_t start = 0;
	uint64_t end   = 0;
	// Test 1: fill the list
	start = get_tsc();
	for (int i = 0; i < count; i++) {
		struct struct_a *new = new_struct_a(words[set_list[i]]);

		list_add(&new->list, &struct_a_list);
	}
	end = get_tsc();

	printf("%luhz\n", (end - start));
	
	int sub_count = 100;
	printf("Test 2: searching through the list for %d randomized names\n",
			sub_count);

	start = get_tsc();
	for (int i = 0; i < sub_count; i++) {
		struct struct_a *entry;
		list_for_each_entry(entry, &struct_a_list, list) {
			if (!strcmp(entry->name, words[get_list[i]])){
				set_priv(entry->priv);
				break;
			}
		}
	}
	end = get_tsc();

	printf("%luhz\n", (end- start));

	sub_count = 500;
	printf("Test 3: searching through the list for %d randomized names\n",
			sub_count);

	start = get_tsc();
	for (int i = 0; i < sub_count; i++) {
		struct struct_a *entry;
		list_for_each_entry(entry, &struct_a_list, list) {
			if (!strcmp(entry->name, words[get_list[i]])){
				set_priv(entry->priv);
				break;
			}
		}
	}
	end = get_tsc();

	printf("%luhz\n", (end- start));

	free_list();
}

static void construct_b(struct struct_b * sb, char *name)
{	
	struct timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	srand(ts.tv_nsec);

	sb->name_len = strlen(name) + 1;
	sb->name = calloc(sb->name_len, sizeof(char));
	strcpy(sb->name, name);
	sb->major = rand();
	sb->minor = rand();
	sb->priv = calloc(1, sizeof(struct priv));
}

void do_test_b(int count)
{
	int set_list[count];
	int get_list[count];
	randomize_index(all_index, LINES);

	memcpy(set_list, all_index, count * sizeof(int));
	memcpy(get_list, set_list, count * sizeof(int));

	randomize_index(get_list, count);

	struct struct_b *b_list = calloc(1, sizeof(struct struct_b));

	printf("Test 1: Filling a dynamic array with %d instances of struct_b\n",
			count);

	uint64_t start = 0;
	uint64_t end   = 0;
	// Test 1: fill the list
	start = get_tsc();
	for (int i = 0; i < count; i++) {
		struct struct_b *_b_list = realloc(b_list, (i+1) * sizeof(struct struct_b));
		if (!_b_list) {
			perror("Failed");
			exit(1);
		}
		b_list = _b_list;

		construct_b(&b_list[i], words[set_list[i]]);
	}
	end = get_tsc();

	printf("%luhz\n", (end - start));

	int sub_count = 100;

	printf("Test 2: searching through the list for %d randomized names\n",
			sub_count);

	start = get_tsc();
	for (int i = 0; i < sub_count; i++) {
		for (int i = 0; i < count; i++) {
			if (!strcmp(b_list[i].name, words[get_list[i]])) {
				set_priv(b_list[i].priv);
				break;
			}
		}
	}
	end = get_tsc();

	printf("%luhz\n", (end- start));

	sub_count = 500;

	printf("Test 3: searching through the list for %d randomized names\n",
			sub_count);

	start = get_tsc();
	for (int i = 0; i < sub_count; i++) {
		for (int i = 0; i < count; i++) {
			if (!strcmp(b_list[i].name, words[get_list[i]])) {
				set_priv(b_list[i].priv);
				break;
			}
		}
	}
	end = get_tsc();

	printf("%luhz\n", (end- start));

	free(b_list);
}