#include <stdio.h>

#include "tests.h"
#define MEMPOOL_DEBUG
#include "alloc.h"

int main(void)
{
	struct mm_struct *mm = get_allocator(4096, 15);

	if (mm) {
		printf("Test 1 (create allocator) successful\n");
	}

	void *test_obj_1 = mm->malloc(mm);

	if (test_obj_1) {
		printf("Test 2 (malloc) successful\n");
	}

	void *test_obj_2 = mm->calloc(mm);
	
	if (test_obj_2) {
		printf("Test 3 (calloc) successful\n");
	}

	mm->free(mm, test_obj_1);
	mm->free(mm, test_obj_2);

	delete_allocator(mm);
}