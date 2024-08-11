#include <time.h>

#include "fuzz-thread.h"

struct timespec ts;

void *thread_start(void *arg)
{
	struct thread_struct *ts = arg;
}