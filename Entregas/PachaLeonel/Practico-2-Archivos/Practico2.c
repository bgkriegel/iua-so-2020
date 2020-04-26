/**************************************************************\
 Autor: Leonel Pacha
 Practico: 2
 Objetivo: Leer y escribir archivos.
 Fecha: 10/04/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>		//Libreria que contiene los modos de apertura de archivos

// Para crear el archivo basta con hacer un 'ls -l / > txt.txt'.

int main () {
	
	int filedesc; //Descriptor de archivo
	char buffer [250]; //Buffer de datos donde pongo los datos del archivos
	int bytes = 2; //El ssize_t es el tipo entero con signo del resultado de sizeof
	
	filedesc = open("txt.txt", O_RDONLY);	/*La funcion open() abre el archivo en el directorio actual, 
											si el archivo no existe, puede crearse.
											retorna un numero que describe al archivo, luego lo tengo que cerrar
											Ahora lo abro en solo lectura, y devuelve -1 si no logro abrir el archivo*/
	
	if (filedesc == -1) {
		
		printf("No se pudo abrir el archivo. \n");
		exit(1);
		
	}
	
	while (bytes > 0){
		
		bytes = read (filedesc, buffer, 250);
		
		/*La funcion read (int fd , void * buf , size_t count ) intenta leer para contar bytes 
		del descriptor de archivo filedesc en el buffer comenzando en buf, la cantidad de count
		Retorna el valor de bytes leidos, pero en caso de error devuelve -1, por eso el while en cada lectura*/
		
		if (bytes > 0)
			printf("%s", buffer); //imprimo lo que acabo de leer	
		
	}
	
	printf("\n............. Finalizó la lectura ..............");
	
	close (filedesc);
	
	
    return 0;
}