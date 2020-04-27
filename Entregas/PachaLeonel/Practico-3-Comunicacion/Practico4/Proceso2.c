/**************************************************************\
 Autor: Leonel Pacha
 Practico: 4
 Objetivo: Finalizar un programa dependiendo del contenido de un 
 archivo, que es controlado por otro proceso.
 Fecha: 20/04/2020
\**************************************************************/

/*Intercambio de mensajes entre dos procesos utilizando un archivo
Sean dos procesos, A y B, los cuales van a 'hablar'
A crea un archivo, ej. comunicador.txt, y escribe dentro de el un mensaje.
Luego lee periodicamente el archivo y espera que el mensaje 'cambie',
cuando descubre que ha cambiado termina.

B verifica que exista el archivo anterior, cuando lo encuentra lo lee,
luego lo sobre-escribe con un mensaje de respuesta, cierra el archivo
y termina.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main () {
	
	int filedesc;
	char com;
	
	filedesc = open ("com.txt", O_WRONLY);
		
	if (filedesc == -1) { 
		printf("No se pudo crear el archivo. \n");
		exit(1);
	}
	
	printf("Soy el proceso 2, voy a modificar el archivo. Ingrese el mensaje\n");
	
	while (1) {
		
		scanf("%s", &com);
		
		if (write (filedesc, &com, 100)) { 	
			
		printf("Acabo de escribir un %s en el archivo\n", com);
			
		close(filedesc);
		
		exit(0);
			
		} else {
		printf("ERROR = No pude escribir en el archivo\n");
		exit(1);
		}
		
		sleep(1);
		
	}
	
	return 0;
	
}