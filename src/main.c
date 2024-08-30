#include <stdio.h>

#include "tests.h"

int main(void)
{
	printf("Loading dictionary\n");
	load_words();
	printf("Words loaded\n");
	printf("Test a with 1000 items\n");
	do_test_a(100000);
	printf("Test b with 1000 items\n");
	do_test_b(100000);
	close_all();
	printf("Exiting\n");
}