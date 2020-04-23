/* 4. Escriba un programa en el cual creamos un proceso y configuramos
   al proceso “padre” para que espere, por medio de la llamada wait(),
   a que termine su hijo antes de proseguir, luego de lo cual debe
   reportar el status de salida del proceso hijo.
   Use la llamada wait(). Se la debe invocar como:

   ...
   wait(&STATUS);
   ...

   Use el status de salida, analícelo por medio de las funciones macro
   definidas en la página de manual de la llamada wait(). */

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

			printf("Padre: Hijo salio con estado %d.\n", WEXITSTATUS(status));
		}
	} else {
		perror("Fallo al crear el fork()");
		_exit(2);				// Salida con error
	}
	return 0;
}
