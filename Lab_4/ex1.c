#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <semaphore.h>

/* Global variables */

int x = 0;
sem_t sync;

/* Thread function */
void *my_func(void *arg)
{
  /* wait for signal from main thread */
  sem_wait(&sync);
  printf("X = %d\n", x);
}

void main()
{
  pthread_t thread;

  /* semaphore sync should be initialized by 0 */

  if (sem_init(&sync, 0, 0) == -1) {
    perror("Could not initialize mylock semaphore");
    exit(2);
  }

  if (pthread_create(&thread, NULL, my_func, NULL) < 0) {
    perror("Error: thread cannot be created");
    exit(1);
  }

  /* perform some operation(s) */
  x = 55;

  /* send signal to the created thread */
  sem_post(&sync);

  /* wait for created thread to terminate */
  pthread_join(thread, NULL);

  /* destroy semaphore sync */
  sem_destroy(&sync);
  exit(0);
}