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
	
	int filedescW, filedescR, bytes = 100;
	char buffer, com;
		
	printf("Soy el proceso 1, voy a crear el archivo. Ingrese el mensaje\n");
		
	scanf("%s", &com);
		
	filedescW = open ("com.txt", O_WRONLY|O_CREAT);
		
	if (filedescW == -1) { 
		printf("No se pudo crear el archivo. \n");
		exit(1);
	}
		
	if (write (filedescW, com, bytes)) { 	
			
		printf("Acabo de escribir un %s en el archivo\n", &com);
			
		close(filedescW);
			
	} else {
		printf("ERROR = No pude escribir en el archivo\n");
		exit(1);
	}
	
	filedescR = open ("com.txt", O_RDONLY);
	
	if (filedescR == -1) { 
		printf("No se pudo abrir el archivo para leerlo. \n");
		exit(1);
	}
	
	while (1) {
		
		sleep(1);
		
		printf("Estoy esperando que se modifique lo que escribi para finalizarme\n");
		
		read (filedescR, &buffer, sizeof(com));
		
		if (com == buffer) {
			printf("\nEl mensaje fue modificado. CHAU\n");
			close(filedescR);
			exit(0);
		}
		
	}
	
	return 0;
	
}