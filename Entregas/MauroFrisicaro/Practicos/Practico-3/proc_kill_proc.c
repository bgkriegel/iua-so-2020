/* 3) Hacer que un proceso finalice a otro: Variante de los anteriores, pero esta vez tenemos dos procesos, A y B.
   A funciona como en 2, B espera un cierto tiempo y luego escribe el archivo esperado por A. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

// Para ejecutar se debe pasar el nombre del archivo a utilizar como argumento.

int main(int argc, char *argv[])
{
	pid_t pid, c_pid;
	int status;

	c_pid = fork();

	// Proceso B - Hijo
	if (c_pid == 0) {

		pid = getpid();
		printf("Hijo: Mi PID es  %d.\n", pid);
		printf("Hijo: Durmiendo 5 segundos.\n");
		sleep(5);

		int fd;
		fd = open(argv[1], O_RDWR | O_CREAT, 0644);

		if (fd == -1) {
			printf("Hijo: Error al abrir el archivo.\n");
		} else {
			dprintf(fd, "0");
		}
	}

	// Proceso A - Padre
	else if (c_pid > 0) {

		pid = wait(&status);

		int fd, i = 0;
		char buff = 2;

		printf("Padre: Ejecutando...\n");

		while (i >= 0) {
			fd = open(argv[1], O_RDONLY);
			read(fd, &buff, 1);
			printf("Padre: Linea leida.\n");

			// Si lee 1 sigue, si lee 0 termina.
			if (buff == '0') {
				printf
					("Padre: Saliendo. OPEN retorno: %d. (iteración %d)\n", fd, i + 1);
				exit(1);
			} else if (buff == '1') {
				printf("Padre: Ejecutando... Iteración (%d)\n", i + 1);
			} else {
				printf("Padre: Ejecutando...\n");
			}
			sleep(i + 1);
			i++;
		}

		if (WIFEXITED(status)) {
			printf("Padre: Hijo salio con estado %d.\n", WEXITSTATUS(status));
		}
	}

	return 0;
}
