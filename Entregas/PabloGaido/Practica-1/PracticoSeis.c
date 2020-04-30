#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void interrumpir(int sig)
{
    	printf("Señal: %d atrapada!\n", sig);
	signal(SIGINT, interrumpir);
	fflush(stdout);
    	return;
}

void suspender(int sig) {
	printf("Señal: %d suspendida!\n", sig);
	exit(0);
}

int main() {
	int it = 1;

	signal(SIGINT, interrumpir);
	
	signal(SIGSTOP, suspender);
 
	
    	while (it!=0)
    	{
        	printf("iteracion: %d\n",it);
		sleep(it);
		it++;
    	}
}

