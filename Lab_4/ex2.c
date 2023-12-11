#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
/* Global variables */
int x = 0;
sem_t m;
/* Thread function */
void *thread(void *arg)
{

    /* critical section */
    sem_wait(&m); /* lock the mutex m */
    x = x + 1;
    sem_post(&m); /* unlock the mutex m */
}
void main()
{

    pthread_t tid[10];
    int i;
    /* semaphore m should be initialized by 1 */
    if (sem_init(&m, 0, 1) == -1)
    {
        perror("Could not initialize mylock semaphore");
        exit(2);
    }
    /* create TEN threads */
    for (i = 0; i < 10; i++)
    {
        if (pthread_create(&tid[i], NULL, thread, NULL) < 0)
        {
            perror("Error: thread cannot be created");
            exit(1);
        }
    }

    /* wait for all created thread to terminate */
    for (i = 0; i < 10; i++)
        pthread_join(tid[i], NULL);
    printf("Final value of x is %d\n", x);
    exit(0);
}