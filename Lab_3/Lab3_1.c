#include <stdio.h> 
#include <unistd.h> /* contains fork prototype */ 
int main(void) 
{ 
	printf("Hello World!\n"); 
	fork( ); 
	printf("I am after forking\n"); 
	printf("\tI am process %d.\n", getpid( )); 
}
