/**************************************************************\
 Autor: Leonel Pacha
 Practico: 2
 Objetivo: Finalizar un programa dependiendo del contenido de un archivo.
 Fecha: 10/04/2020
\**************************************************************/

// Si contiene un valor '1' entonces sigue ejecutandose
// Si contiene el valor '0' termina

// Si quisiera crear el txt.txt con el 1 o el 0 por consola uso 'echo "1" >> txt.txt' 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main () {
	
	int filedesc;
	char buffer = 5;
	
	printf("Soy un programa que ve el contenido de un archivo, (1 = me ejecuto) o (0 = termino)\n");

	while (1){
		
		filedesc = open ("txt.txt", O_RDONLY);
		
		if (filedesc == -1) { 
			
			printf("No se pudo abrir el archivo. \n");
			exit(1);
		}
		
		read (filedesc, &buffer, 1);	// Le pongo el & ya que espera un puntero
		
		if (buffer == '1') {
			printf ("Sigo ejecutandome...\n");
		} else if (buffer == '0') {
			printf("Oh, encontre el '0' en el archivo. El filedesc vale : %d\n", filedesc);
			exit(0);
		} else {
			printf("El archivo contiene otro caracter, por lo tanto no lo reconozco y lo sigo ejecutando :)\n");
		}
		
		sleep(3);
	}
	
	return 0;
}