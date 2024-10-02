#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "tests.h"

#define WORDS_MEM_SZ LINES * sizeof(size_t)

const char *data_structure_names[] = {
	"linked list", "dynamic array",
};

const char *allocation_method_names[] = {
	"libc allocator", "memory pool",
};

const char *operation_names[] = {
	"create", "read", "update", "delete"
};

static void init_clock(struct test_manager *manager)
{
	clock_gettime(CLOCK_MONOTONIC_RAW, &manager->ts);
}

static void init_index(struct test_manager *manager)
{
	for (size_t i = 0; i < LINES; i++) {
		manager->common_index[i] = i;
	}
}

void randomize_index(struct timespec *ts, int *index, int n)
{
	srand(ts->tv_nsec);

	for (size_t i = 0; i < n; i++) {
		int swap_idx = rand() % n;
		int tmp = index[i];
		index[i] = index[swap_idx];
		index[swap_idx] = tmp;
	}
}

static void init_dictionary(struct test_manager *manager)
{
	int fd = open("words.txt", O_RDWR);

	struct stat st;
	fstat(fd, &st);

	/* 
	 * I'm going to cheat a little bit for the array of words. Instead of
	 * calling {m|c}alloc repeatedly I'm going to mmap the words list and
	 * char **words.
	 */
	manager->word_list_size = st.st_size;
	char *w_buf = mmap(NULL,manager->word_list_size, PROT_WRITE | PROT_READ, 
	                   MAP_PRIVATE, fd, 0);
	close(fd);

    manager->word_list = mmap(NULL, WORDS_MEM_SZ, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS,
	             -1, 0);

	memset(manager->word_list,0,WORDS_MEM_SZ);

	char **words_cursor = manager->word_list;
	*words_cursor = w_buf;

	for (char *cursor = w_buf; *cursor; cursor++) {
		if (*cursor == '\n') {
			*cursor = 0;
			*(++words_cursor) = ++cursor;
		}
	}
}

static inline void add_result(struct test_manager *manager, struct test_result *result)
{
	list_add(&result->list_node, &manager->results);
}

static void print_one_result(struct test_result *result)
{	
	printf("%s\t%s\t%s\t%lu\n", data_structure_names[result->structure],
		   allocation_method_names[result->method], 
		   operation_names[result->operation], result->runtime_hz);
}

static void print_results(struct test_manager *manager)
{
	struct test_result *result;
	printf("Struct:\t\tMethod:\t\tOperation:\tTime:\n");
	list_for_each_entry(result, &manager->results, list_node) {
		print_one_result(result);
	}
}

static void close_manager(struct test_manager *manager)
{
	munmap(*manager->word_list, WORDS_MEM_SZ);
	munmap(manager->word_list, manager->word_list_size);
}

static int write_result_header(FILE *filp)
{
	errno = 0;
	int err = fprintf(filp, "\nData Structure,Allocation Method,Operation,Hz,\n");
	if (err < 0) {
		if (!errno)
			errno = EIO;
		return -1;
	}
	return 0;
}

static int write_one_result(FILE *filp, struct test_result *result)
{
	errno = 0;
	int err = fprintf(filp, "%s,%s,%s,%lu\n",
					  data_structure_names[result->structure],
					  allocation_method_names[result->method],
					  operation_names[result->operation],
					  result->runtime_hz);
	if (err < 0) {
		if (!errno)
			errno = EIO;
		return -1;
	}
	return 0;
}

static int save_results(struct test_manager *manager, char *path)
{
	FILE *filp = fopen(path, "a");
	if (!filp) {
		int _err = errno;
		printf("Could not open %s:\nError %d (%s)\n", path, _err,
			   strerror(_err));
		errno = _err;
		return -1;
	}
	
	if (write_result_header(filp)) {
		int _errno = errno;
		fclose(filp);
		printf("Failed to write result header:\nError %d (%s)\n", _errno, 
			   strerror(_errno));
		errno = _errno;
		return -1;
	}

	struct test_result *result;
	list_for_each_entry(result, &manager->results, list_node) {
		if (write_one_result(filp, result)) {
			int _errno = errno;
			printf("Failed to write result row:\nError %d (%s)\n", _errno,
			       strerror(_errno));
			errno = _errno;
			return -1;
		}
	}

	return 0;
}

static uint64_t do_one_test(struct test_manager *manager, 
						    struct mm_struct *allocator, test_fn fn)
{
	errno = 0;
	uint64_t tsc_start = get_tsc();
	int err = fn(manager, allocator);
	uint64_t tsc_end = get_tsc();

	if (err) {
		return err;
	}

	return tsc_end - tsc_start;
}

void init_manager(struct test_manager *new)
{
	init_clock(new);
	init_dictionary(new);
	init_index(new);

	INIT_LIST_HEAD(&new->results);

	new->add_result = add_result;
	new->print_results = print_results;
	new->save_results = save_results;
	new->do_one_test = do_one_test;
	new->close_base_manager = close_manager;
}