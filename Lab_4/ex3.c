#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/* Global variables */
int x = 1;
sem_t m;

/* Thread function */
void *thread(void *arg)
{
    int n = 1;
    /* critical section */
    sem_wait(&m); /* lock the mutex m */

    /* Print the thread ID and the value of x */
    printf("TID %lu Value X = %d\n", pthread_self(), x);

    x = x + 1;

    sem_post(&m); /* unlock the mutex m */

    return NULL;
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

    printf("Final value of x is %d\n", x-1);

    exit(0);
}