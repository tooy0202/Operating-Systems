#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
    int pid;
    pid = fork(); /* Duplicate. Child and parent continue from here */

    if (pid != 0) /* pid is non-zero, so I must be the parent */
    {
        while (1) /* Never terminate and never execute a wait() */
        {
            sleep(10); /* stop executing for 10 seconds */

            // Print the student's name every 10-15 seconds
            printf("Student Name: 65543206086-2 Athit Suntalodom\n");
            
        }
    }
    else /* pid is zero, so I must be the child */
    {
        exit(42); /* exit with any number */
    }

    return 0;
}
