#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "threadlib.h"

typedef struct __counter_args {
	int *nLoops;
	int *count;
	struct lock_t *lock;
} counter_args;


void *counter(void *arg)
{
	counter_args *args= (counter_args*)arg;

	int i;

	for(i = 0; i < *args->nLoops; i++)
	{
		lock_acquire(args->lock);
		(*args->count)++;
		lock_release(args->lock);
	}

	return NULL;
}

void *doNothing(void * nothing)
{
	return NULL;
}

int
main(int argc, char *argv[])
{
	if(argc != 3)
	{
//		if(argc != 2)
//		{
			printf(1, "Usage: threadtest numberOfThreads loopCount");
			exit();
//		}
//		
//		int nThreads = atoi(argv[1]);
//		int j;
//		for(j = 0; j < nThreads; j++)
//		{
//			thread_create(doNothing, NULL); 
//		}
//		
//		printf(1, "Parent has %d bytes of memory.", proc->sz);
//		growproc(4096);
//		printf(1, "Parent now has %d bytes of memory.", proc->sz);
//		
//		for(j = 0; j < 64; j++)
//		{
//			if(&ptable.proc[j] != NULL)				// expanded for debugging
//				if(ptable.proc[j].parent == proc)
//					printf(1, "Child with pid = %d has %d bytes of memory.", j, ptable.proc[j].sz);
//		}
//
//		for(j = 0; j < nThreads; j++)
//		{
//			thread_join();
//		}
//
	}
	
	int nThreads = atoi(argv[1]);
	int nLoops =  atoi(argv[2]);
	
	int count = 0;
	struct lock_t lock;
	lock_init(&lock);

	counter_args args;
	args.nLoops = &nLoops;
	args.count = &count;
	args.lock = &lock;

	void * a = (void*) &args;

	int i;
	for(i = 0; i < nThreads; i++)
	{
		thread_create(counter, a);
	}

	for(i = 0; i < nThreads; i++)
	{
		thread_join();
	}
	
	printf(1, "Result is: %d\n", count);
	exit();
}

