#include <stdio.h> 
main() 
{ 
	int pid ; 
	printf("I'am the original process with PID %d and PPID %d.\n", getpid(), 
	getppid()) ; 
	pid = fork ( ) ; /* Duplicate. Child and parent continue from here */ 
	if ( pid != 0 ) /* pid is non-zero,so I must be the parent*/ 
	{ 
		printf("I'am the parent with PID %d and PPID %d.\n", getpid(), getppid()) ; 
		printf("My child's PID is %d\n", pid ) ; 
	} 
	else /* pid is zero, so I must be the child */ 
	{ 
		sleep(4); /* make sure that the parent terminates first */ 
		printf("I'm the child with PID %d and PPID %d.\n", getpid(), getppid()) ; 
	} 
	printf ("PID %d terminates.\n", getpid()) ; 
}
