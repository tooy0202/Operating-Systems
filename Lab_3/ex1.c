#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {

	char *who;
	int i;

	if(fork()){
		who = "athit suntalodom.";
	} else{
		who = "child";
	}

	for (i = 0; i<6;i++){
		printf("*frok1: %s\n", who);
	}

	exit (0);

}


