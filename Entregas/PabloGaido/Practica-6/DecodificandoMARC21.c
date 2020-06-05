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
	char lenght[5];
	int indice = 0;

	fd = open("osbooks.iso2709", O_RDONLY);	//Verifico que el archivo existe
	if (fd == -1) {
		printf("Error de lectura\n");
		exit(1);
	}

	while (read(fd, length, indice + 5)) {	//leo el tamaño del FIELD

		lenght[0] = length[indice];  
		lenght[1] = length[indice + 1]; 
		lenght[2] = length[indice + 2]; 
		lenght[3] = length[indice + 3]; 
		lenght[4] = length[indice + 4];	//uno los caracteres donde se encuentra el tamaño
		largoArchivo = atoi(lenght);


		procesarPartes(fd, largoArchivo, indice);

		indice = indice + largoArchivo;	//marco el comienzo del proximo FIELD
	}


}



void procesarPartes(int fd, int lenght, int indice)
{
	char sector[99999];
	char ubicacion[5];

	read(fd, sector, lenght + indice);	//accedo a un FIELD del archivo. indice representa el tamaño del field anteior, por lo que me lo salteo

	for (int i = 0; i < 28; i++) {	//recorro los "address y ubicacion" de los datos. Por defecto puse que tiene 28 datos

		lenght[0] = sector[(24 + 3) + (i * 12) + indice]; 
		lenght[1] = sector[(24 + 4) + (i * 12) + indice]; 
		lenght[2] = sector[(24 + 5) + (i * 12) + indice]; 
		lenght[3] = sector[(24 + 6) + (i * 12) + indice];	//uno los caracteres donde se encuentra el tamaño
		lenght[4] = "";

		ubicacion[0] = sector[(24 + 7) + (i * 12) + indice]; 
		ubicacion[1] = sector[(24 + 8) + (i * 12) + indice]; 
		ubicacion[2] = sector[(24 + 9) + (i * 12) + indice]; 
		ubicacion[3] = sector[(24 + 10) + (i * 12) + indice]; 
		ubicacion[4] = sector[(24 + 11) + (i * 12) + indice];	//uno los caracteres donde se encuentra la ubicacion


		for (int j = atoi(ubicacion); j < atoi(lenght) + j; j++) {

			printf("%c", sector[j]);	//imprimo los datos caracter por caracter


		}

		printf("\n");  //Separo los datos con un salto de pagina

	}


}
