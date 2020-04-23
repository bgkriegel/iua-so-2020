/* Todo proceso 'trabaja' con valores que tiene en su memoria.
   Estos valores los puede 'leer' de archivos externos.

   Desde el punto de vista de un proceso un 'archivo' es algo que accede utilizando un 'file descriptor'
   como el que se obtiene por medio de la llamada al sistema open().

   Vamos a probar diferentes maneras de comunicarnos o comunicar entre si procesos utilizando diferentes tipos de mecanismos
   que desde el punto de vista del proceso son casi todos como leer/escribir archivos.

   1) Finalizar un programa utilizando un archivo externo: Escriba un programa que verifique periódicamente la
   existencia de un archivo (elija el nombre), si descubre que existe entonces termina. */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{

	int fd, i = 0;

	printf("Ejecutando...\n");

	while (i >= 0) {
		fd = open("file", O_RDONLY); // Va a dejar de ejecutar cuando se cree el archivo file.

		if (fd != -1) {
			printf(">> Saliendo, OPEN retorno: %d. (iteración %d) <<\n", fd, i + 1);
			exit(1);
		}

		printf("Ejecutando... (iteracion %d)\n", i + 1);
		sleep(i + 1);
		i++;
	}

	return 0;
}
