#include <stdio.h>

#include "tests.h"

int main(void)
{
	struct mm_struct *mm = get_mempool_allocator(4096, 15);

	if (mm) {
		printf("Success 1\n");
	}
}