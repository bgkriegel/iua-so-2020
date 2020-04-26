/**************************************************************\
 Autor: Leonel Pacha
 Practico: 1
 Objetivo: Finalizar un programa utilizando un archivo externo.
 Fecha: 10/04/2020
\**************************************************************/

// Para ello, verificar periodicamente la existencia de un archivo. Si exite, termina.

// Si ejecuto el programa sin el txt.txt en el directorio en el cual se esta ejecutando, muestra 
// el printf del while... ahora, si creo el txt.txt desde otra consola con touch txt.txt, muestra el if del while

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main () {
	
	int filedesc;
	
	printf("Soy un programa que verificare si exite un archivo, si existe, me cerraré\n");

	while (1){
		
		filedesc = open ("txt.txt", O_RDONLY);
		
		if (filedesc != -1) { 		// Aca no pongo == -1 ya que quiero que sea erroneo 
			
			printf("Oh, encontre el archivo. El filedesc vale : %d\n", filedesc);
			exit(0);
			
		}
		
		printf(":( No encuentro el archivo todavia\n");
		sleep(3);
		
	}
	
	return 0;
}