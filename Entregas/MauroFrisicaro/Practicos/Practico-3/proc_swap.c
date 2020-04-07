/* 4) Intercambio de mensajes entre dos procesos utilizando un archivo: Sean dos procesos A y B, los cuales van a 'hablar'

   A crea un archivo, ej. comunicador.txt, y escribe dentro de el un mensaje.
   Luego lee periodicamente el archivo y espera que el mensaje 'cambie', cuando descubre que ha cambiado termina.

   B verifica que exista el archivo anterior, cuando lo encuentra lo lee,
   luego lo sobre-escribe con un mensaje de respuesta, cierra el archivo y termina. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

// Para ejecutar se debe pasar el nombre del archivo a utilizar como argumento.

int main(int argc, char *argv[])
{
	int status;

	c_pid = fork();

	// Proceso A - Hijo
	if (c_pid == 0) {
		int fd;

		printf("Hijo: Voy a crear el archivo.\n");
		fd = open(argv[1], O_RDWR | O_CREAT, 0644);

		if (fd == -1) {
			printf("Hijo: Error al abrir el archivo.\n");
		} else {
			printf("Hijo: Ahora voy a escribir Hola!");
			dprintf(fd, "HOla!");
			
			
			
			
			
		}
	}

	// Proceso B - Padre
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
