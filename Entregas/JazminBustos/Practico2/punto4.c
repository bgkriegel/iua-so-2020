#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>



int main(int argc, char *argv[])
{


	//for (int i = 0; i < argc; i++) {
	//  printf("%s\n", argv[i]);
	//}


	int fd, archivoNuevo;
	char buf[10000];
	ssize_t nr_bytes;


	fd = open(argv[1], O_RDONLY);	//Lee el archivo ingresado por consola

	if (fd == -1) {

		printf("Error ar leer el archivo");
		exit(1);

	} else {



		nr_bytes = read(fd, buf, 5000);	//Extraigo el contenido de "archivo.txt" , "solo los primeros 500 bytes de texto"
		close((int) fd);

		if (nr_bytes == 0) {

			printf("Archivo vacio");
			exit(1);

		}

		archivoNuevo = open("ArchivoNuevo.txt", O_RDWR | O_CREAT, 0644);	//Creo el archivo nuevo
		write(archivoNuevo, buf, nr_bytes);	//Escribo el contenido de -buf- dentro de -archivoNuevo-
		printf(buf);			//Muestro el contenido transferido al nuevo archivo

	}


}
