#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "threadlib.h"

struct lock_t lock;

void thread_create(void *(*start_routine)(void*), void *arg)
{
  void *nSp = malloc(4096);
  int rc;
  rc = clone(nSp, 4096);

  if(rc == 0)
  {
    (*start_routine)(arg);
    exit();
  }
}

void thread_join()
{
  wait();
}

void lock_init(struct lock_t *lk)
{
    lk->locked = 0;
}

void lock_acquire(struct lock_t *lk)
{
  while(xchg(&lk->locked, 1) != 0)
      ;
}

void lock_release(struct lock_t *lk)
{
  xchg(&lk->locked, 0);
}