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

static char **words;
static int words_fd;

static int all_index[LINES];

static LIST_HEAD(struct_a_list);

static void init_index(void)
{
	for (size_t i = 0; i < LINES; i++) {
		all_index[i] = i;
	}
}

static void randomize_index(int *index, int n)
{
	struct timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	srand(ts.tv_nsec);

	for (size_t i = 0; i < n; i++) {
		int swap_idx = rand() % n;
		int tmp = index[i];
		index[i] = index[swap_idx];
		index[swap_idx] = tmp;
	}
}

void load_words(void)
{
	words_fd = open("words.txt", O_RDWR);

	struct stat st;
	fstat(words_fd, &st);

	/* 
	 * I'm going to cheat a little bit for the array of words. Instead of
	 * calling {m|c}alloc repeatedly I'm going to mmap the words list and
	 * char **words.
	 */

	char *w_buf = mmap(NULL,st.st_size, PROT_WRITE | PROT_READ, 
	                   MAP_PRIVATE, words_fd, 0);

    words = mmap(NULL, WORDS_MEM_SZ, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS,
	             -1, 0);

	memset(words,0,WORDS_MEM_SZ);

	char **words_cursor = words;
	*words_cursor = w_buf;

	for (char *cursor = w_buf; *cursor; cursor++) {
		if (*cursor == '\n') {
			*cursor = 0;
			*(++words_cursor) = ++cursor;
		}
	}

	init_index();
}

void close_all(void)
{
	struct stat st;
	fstat(words_fd, &st);
	munmap(*words, WORDS_MEM_SZ);
	munmap(words, st.st_size);
	close(words_fd);	
}

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

static struct struct_b *construct_b(struct struct_b * sb, char *name)
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