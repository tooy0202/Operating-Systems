#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <math.h>
#include <time.h>

int main (int argc, char *argv[]) {
	
	char *who;
	int status;
	time_t t;
	if(fork()){
		who = "athit";
		printf("pi =%f\n", 4*atan(1));
		time(&t);
		printf("%s",ctime(&t));
		wait (&status);
		exit(0);
	} else{
		who = "child";
		execlp ("/bin/my-script","my-script","a","b",(char*)0);
	}

}
