#include "user.h"

void
counter(int * nLoops, int * count, lock_t * lock)
{
	int i;

	for(i = 0; i < *nLoops; i++)
	{
		lock_acquire(lock);
		(*count)++;
		lock_release(lock);
	}

	return 0;
}


int
main(void * argv, int argc)
{
	if(argc != 3)
	{
		printf(1, "Usage: threadtest numberOfThreads loopCount");
		return -1;
	}
	
	int * nThreads = (int*) &argv[1];
	int * nLoops = (int*) &argv[2];
	
	int * count;
	*count = 0;
	lock_t * lock;
	lock_init(lock);

	int i;
	for(i = 0; i < nThreads; i++)
	{
		thread_create(counter(), nLoops, count, lock);
	}

	for(i = 0; i < nThreads; i++)
	{
		thread_join();
	}
	
	printf(1, "%d\n", count);
	return 0;
}

