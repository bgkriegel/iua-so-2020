#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>


void signalSuspend(int sig_num){
	printf("Para finalizar el proceso presione Ctrl + Z\n");
	signal(SIGINT, signalSuspend);
	fflush(stdout);
}

void signalTerminate(int sig_num){
	printf("El proceso se esta cerrando. \n");
	exit(0);
}

int main()
{
	printf("Presione Ctrl + C para pausar el proceso\n");
	printf("Presione Ctrl + Z para detener el proceso\n");

	signal(SIGINT, signalSuspend);
	signal(SIGTSTP, signalTerminate);

	// Infinite loop
	while (1) {
	}
	return 0;


}