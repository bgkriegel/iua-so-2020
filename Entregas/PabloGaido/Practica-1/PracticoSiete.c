#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

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

	int pid;
	int my_pid;
	int status = 0;
	pid = fork();

	if(pid==0) {
	
		printf("Este es el hijo");
		my_pid = getpid();
		printf("Mi pid es: %d \n", my_pid);
		signal(SIGINT, interrumpir);
		signal(SIGSTOP, suspender);
		sleep(5);
		exit(3);

	} else {
		wait(&status);
		if (WIFEXITED(status)) {
		    	printf("Este es el padre");
		    	my_pid = getpid();
		    	printf("Mi pid es: %d \n", my_pid);
		    	printf("Proceso hijo terminó con estado: %d \n", status);
		    	WEXITSTATUS(status);
		} else {
			printf("Estado de salida: %d \n", status);
		    	printf("Ocurrió un error \n");
		    	printf("Estado de salida: %d \n", status);
		    	return -1;
		}
		
	}
	return 0;
}

