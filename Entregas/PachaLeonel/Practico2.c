/**************************************************************\
 Autor: Leonel Pacha
 Practico: 2
 Objetivo: Estudiar la llamada al sistema Fork.
 Fecha: 25/03/2020
\**************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	
	int pid, pid2;
	
	pid = fork();
	
	/* la funcion fork() crea un nuevo proceso que es la copia
	identica al proceso que la invoco.
	En el proceso donde se invoco, la funcion devuelve el ID del nuevo proceso
	y en el proceso COPIA, la funcion retorna 0*/
	
	if (pid != 0) {
		
		printf("Soy el proceso padre\n");		//Se le dice padre al que invoco la funcion
		
		pid2 = getpid();
		
		printf(" Mi ID de proceso es %d\n", pid2);
		
	} else {
		
		printf("Soy el proceso hijo\n");		//Se le dice hijo al nuevo proceso COPIA
		
		pid2 = getpid();
		
		printf(" Mi ID de proceso es %d\n", pid2);
		
	}
		
	return 0;
}