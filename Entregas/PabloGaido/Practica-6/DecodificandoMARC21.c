#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void procesarPartes(int fd, int tamanio, int indice);


int main()
{

	char length[99999];
	int fd;
	int largoArchivo = 0;
	int i = 0;
	int tamanio = 0;
	int indice = 0;

	fd = open("osbooks.iso2709", O_RDONLY);	//Verifico que el archivo existe
	if (fd == -1) {
		printf("Error de lectura\n");
		exit(1);
	}

	while (read(fd, length, indice + 5)) {	//leo el tamaño del FIELD

		tamanio = length[indice] + length[indice + 1] + length[indice + 2] + length[indice + 3] + length[indice + 4];	//uno los caracteres donde se encuentra el tamaño
		largoArchivo = atoi(tamanio);


		procesarPartes(fd, largoArchivo, indice);

		indice = indice + largoArchivo;	//marco el comienzo del proximo FIELD
	}


}



void procesarPartes(int fd, int tamanio, int indice)
{
	char sector[99999];
	int ubicacion = 0;

	read(fd, sector, tamanio + indice);	//accedo a un FIELD del archivo. indice representa el tamaño del field anteior, por lo que me lo salteo

	for (int i = 0; i < 28; i++) {	//recorro los "address y ubicacion" de los datos. Por defecto puse que tiene 28 datos

		tamanio = sector[(24 + 3) + (i * 12) + indice] + sector[(24 + 4) + (i * 12) + indice] + sector[(24 + 5) + (i * 12) + indice] + sector[(24 + 6) + (i * 12) + indice];	//uno los caracteres donde se encuentra el tamaño

		ubicacion = sector[(24 + 7) + (i * 12) + indice] + sector[(24 + 8) + (i * 12) + indice] + sector[(24 + 9) + (i * 12) + indice] + sector[(24 + 10) + (i * 12) + indice] + sector[(24 + 11) + (i * 12) + indice];	//uno los caracteres donde se encuentra la ubicacion


		for (int j = atoi(ubicacion); j < atoi(tamanio) + j; j++) {

			printf("%c", sector[j]);	//imprimo los datos caracter por caracter


		}

		printf("\n");  //Separo los datos con un salto de pagina

	}


}
