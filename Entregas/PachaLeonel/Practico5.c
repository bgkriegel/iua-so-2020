/**************************************************************\
 Autor: Leonel Pacha
 Practico: 5
 Objetivo: Observar el estado de salida de un proceso en ejecucion por tiempo indefinido.
 Fecha: 25/03/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	
	int pid, pid2, status, i = 1;
	
	pid = fork();
	
	if ( pid == 0 ) {		
	
		printf("Soy el proceso hijo");		
		
		pid2 = getpid();
		
		printf(" Mi ID de proceso es %d\n", pid2);
		
		while (i != 0) {	//Bucle infinito
			
			printf("Sigo en el proceso hijo, repeticion %d\n", i);
			
			sleep(4);
			
			i++;
			
		}
		
		/*Con ctrl + z, hago que el proceso se detenga o termine, esta señal se envia al proceso
		y su estado de salida "0" que verifica WIFEXITED, no es cero, por lo tanto WIFEXITED retorna falso*/
	
	} else {		
	
		wait(&status);		
		
		if (WIFEXITED(status)) {		//retorna verdadero si el hijo finalizo correctamente, en este caso NO
		
			printf("Soy el proceso padre");
		
			pid2 = getpid();
		
			printf(" Mi ID de proceso es %d\n", pid2);
			
			printf(" Mi hijo finalizo con un estado: %d\n", status);
			
			WEXITSTATUS(status);		
		
		} else {			//si el hijo no finalizo bien
		
			printf("Ocurrio un error en la espera del proceso\n");
			
			printf("El estado de salida es: %d\n", status);
			
			return -1;
		
		}	
	
	}
	
	return 0;
}