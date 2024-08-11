#ifndef FUZZ_THREAD_H
#define FUZZ_THREAD_H

/* Declares the functions and structures for the fuzzer thread.
 *
 * The fuzzer is meant to simulate the memory use of a fully-fledged
 * application, especially in terms of making allocations that complicate
 * the job of the standard library allocator. */

/*
 * Passed as the argument to thread_start. Specifies how many objects of
 * each size and how many child threads is to create.
 */
struct thread_struct {
	int nr_small_objs;
	int nr_med_objs;
	int nr_lg_objs;
	int nr_children;
};

void *thread_start(void *);

#endif /* FUZZ_THREAD_H */