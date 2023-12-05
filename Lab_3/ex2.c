#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
	
	int i;
	char *who;
	int n;

	if(fork()){
		who = "athit suntalodom";
		n = 2;
	} else{
		who = "child";
		n = 1;
	}

	for (i = 1; i<=10 ;i++){
		fprintf(stdout,"*%2d. %7s: my pid = %6d, ppid = %6d\n ",i,who,getpid(),getppid());
		fflush (stdout);
		sleep (n);
	}

	exit (0);

}
