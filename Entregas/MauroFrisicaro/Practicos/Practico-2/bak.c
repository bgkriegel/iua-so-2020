/* Escriba un programa que reciba por linea de comando el nombre de un archivo y lo copie en un archivo con la extension ".bak".
   Use open(), close(), read() y write().

   Tip: Usará open() dos veces, una el leer el archivo origen y otra al crear y escribir en el archivo de destino.
   Para el segundo caso puede utilizar fd = open("test.txt", O_RDWR|O_CREAT, 0644);
   o lo que es lo mismo fd = open("test.txt", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH );
   vea la página de manual 'man 2 open'

   Tip: El programa en si tiene tres partes
     - abrir los archivos
     - recorrer (loop) el origen y escribir en destino
     - cerrar los archivos
   el loop termina analizando el valor retornado por read() */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

	int fd, fdbak;
	char buf[10000]; // Tamaño del Buffer en Bytes
	ssize_t nr_bytes;

	fd = open(argv[1], O_RDONLY);
	fdbak = open("copy.bak", O_RDWR | O_CREAT, 0644);

	if (fd == -1) {
		printf("Error al abrir el archivo.\n");
	} else {
		nr_bytes = read(fd, buf, 10000); // Va a leer 10 mil caracteres
		close(fd);

		if (nr_bytes == 0) {
			printf("Archivo vacio!\n");
		} else {
			dprintf(fdbak, "%s", buf);
		}
	}

	return 0;
}
