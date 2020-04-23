/* 4) Intercambio de mensajes entre dos procesos utilizando un archivo: Sean dos procesos A y B, los cuales van a 'hablar'

   A crea un archivo, ej. comunicador.txt, y escribe dentro de el un mensaje.
   Luego lee periodicamente el archivo y espera que el mensaje 'cambie', cuando descubre que ha cambiado termina.

   B verifica que exista el archivo anterior, cuando lo encuentra lo lee,
   luego lo sobre-escribe con un mensaje de respuesta, cierra el archivo y termina. */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

// Para ejecutar se debe pasar el nombre del archivo a utilizar como argumento.

int main(int argc, char *argv[])
{
	pid_t pid = fork();

	// Proceso A - Hijo
	if (pid == 0) {
		int fd, i = 0;
		char buff[100];

		printf("Hijo: Voy a crear el archivo.\n");
		fd = open(argv[1], O_RDWR | O_CREAT, 0644);

		if (fd == -1) {
			printf("Hijo: Error al abrir el archivo.\n");
		} else {
			printf("Hijo: Ahora voy a escribir Hola!\n");
			dprintf(fd, "Hola!");
			close(fd);

			while (i >= 0) {
				fd = open(argv[1], O_RDONLY);
				read(fd, &buff, 100);
				printf("BUFF: %s \n", buff);

				if (strcmp(buff, "Hola!")) {
					printf("Hijo: Saliendo. (iteración %d)\n", i + 1);
					close(fd);
					return 1;
				} else {
					printf("Hijo: Ahora voy a leer hasta que cambie...\n");
				}
				sleep(i + 1);
				i++;
			}
		}
	}
	// Proceso B - Padre
	else if (pid > 0) {

		int fd;
		char buf[100];

		fd = open(argv[1], O_RDWR);
		read(fd, buf, 100);
		dprintf(fd, "Que tal!?\n");
		close(fd);

	}

	return 0;
}
