#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void signalI(int sig){
	printf("Signal iterrupted. Signal: %d\n", sig);
	signal(SIGINT, signalI);
	fflush(stdout);
}

void signalS(int sig){
	printf("Signal suspended. \n");
	exit(0);
}

int main() {

	signal(SIGINT, signalI);
	
	signal(SIGSTOP, signalS);
	
	while (1) {
	}
	return 0;
}