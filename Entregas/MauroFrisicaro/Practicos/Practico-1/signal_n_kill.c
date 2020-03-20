/* 7. Escriba un programa que cree un hijo, capture las mismas señales del programa anterior,
   se las reenvie al hijo y reproduzca la funcionalidad previa, es decir que el hijo escriba
   un mensaje para la primer señal y termine para la segunda, al terminar el hijo también
   debe terminar el padre. */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Signal Handler for SIGINT
void signalTerminate(int sig_num)
{
	printf("\n Este proceso no se puede terminar con Ctrl+C. \n");

	// Reset handler to catch SIGINT next time
	signal(SIGINT, signalTerminate);
	fflush(stdout);
}

// Signal Handler for SIGTSTP
void signalSuspend(int sig_num)
{
	printf("\n Este proceso se termina con Ctrl+Z. \n");
	exit(0);
}

int main()
{
	pid_t pid, c_pid;
	int status;

	c_pid = fork();

	if (c_pid == 0) {
		pid = getpid();
		printf("Hijo: Mi PID es  %d.\n", pid);
		printf("Hijo: Durmiendo 2 segundos y saliendo con estado 12.\n");

		sleep(2);				// Sleeps for 2 seconds.
		exit(12);				// Exit with status 12.

	} else if (c_pid > 0) {
		pid = wait(&status);

		// WIFEXITED returns  true if the child terminated normally.
		if (WIFEXITED(status)) {


			signal(SIGINT, signalTerminate);
			signal(SIGTSTP, signalSuspend);

			// Loop infinito
			while (1) {
				kill(pid, 18);
			}
		}
	}
	return 0;
}

// Verificar salida: echo $?
