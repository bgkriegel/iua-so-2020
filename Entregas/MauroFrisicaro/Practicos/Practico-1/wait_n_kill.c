/*  5. Escriba un programa similar al anterior, pero modificado de modo
   que el hijo quede en espera indefinida, luego desde una terminal envíe
   una señal (por medio del comando kill para que termine y observe el
   comportamiento del status de salida.
   Investigue las señales posibles por medio de man 7 signal. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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


			// Loop infinito
			while (1) {
				kill(pid, 18);
			}
		}
	}
	return 0;
}

// Verificar salida: echo $?
