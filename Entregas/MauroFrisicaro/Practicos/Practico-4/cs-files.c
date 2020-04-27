/* 1) Cliente-Servidor con archivos.
   Exploraremos la posibilidad de "comunicar" dos procesos mediante archivos externos.
   Escriba un programa que "cree" dos archivos, a-inout y b-inout.
   Luego deberá crear dos hijos, cada hijo deberá abrir los archivos PERO de modo que el primer hijo abra "a" para lectura
   y "b" para escritura, en cambio el segundo abrira "a" para escritura y "b" para lectura.
   Una vez realizado esto el primer hijo debera obtener la hora del sistema (usando ctime()), escribira esta informacion en "b",
   cuando esto ocurra, el segundo proceso hijo obtendra a su vez la hora y la leerra de  "b", y la mostrara por pantalla.
   Al finalizar ambos procesos hijos el padre deberá reportar el estado de terminacion. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>

int main()
{

	int pid1, pid2, fd1, fd2, status;
	char buff1, buff2;
	time_t timeact;

	fd1 = creat("tub-a", 0644);
	fd2 = creat("tub-b", 0644);

	pid1 = fork();

	if(pid1 == 0) {
		printf("HIJO_1: Mi ID es %d, el ID de mi padre es %d.\n", getpid(), getppid());

		fd1 = open("tub-a", O_RDONLY);
		fd2 = open("tub-b", O_WRONLY);

		time(&timeact);
		buff1 = ctime(&timeact);

		write(fd2, &buff1, sizeof(buff1));

		close(fd1);
		close(fd2);

		return 0;
	}

	pid2 = fork();

	if(pid2 == 0) {

		printf("HIJO_2: Mi ID es %d, el ID de mi padre es %d.\n", getpid(), getppid());

		fd1 = open("tub-a", O_WRONLY);
		fd2 = open("tub-b", O_RDONLY);

		read(fd2, &buff2, sizeof(buff2));

		close(fd1);
		close(fd2);

		return 0;
	} else {

		wait(&status);

		if(WIFEXITED(status)) {
			printf("PADRE: Mi ID es %d, mi hijo finalizo con estado %d.\n", getpid(), status);
			WEXITSTATUS(status);
		} else {
			printf("Error.\n");
			return -1;
		}
	}

	return 0;

}
