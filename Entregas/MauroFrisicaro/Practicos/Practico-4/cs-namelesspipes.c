/* Cliente-Servidor con pipes sin nombre.
   Escribiremos un programa que creara dos hijos los cuales se comunicaran utilizando pipes sin nombre.
   Uno de los hijos obtiene la hora del sistema como antes, y envía ese dato utilizando pipes.
   El segundo recibe los datos y los muestra por pantalla. */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
	int pid1, pid2, pd[2];
	char buff1, buff2;
	time_t timeact;

	pipe(pd);

	pid1 = fork();
	if(pid1 == 0) {
		time(&timeact);
		buff1 = ctime(&timeact);
		write(pd[0], &buff1, sizeof(buff1));
		return 0;
	}

	pid2 = fork();
	if(pid2 == 0) {
		read(pd[1], &buff2, sizeof(buff2));
		printf("Buffer: %d \n", buff2);
	}

	return 0;
}
