/**************************************************************\
 Autor: Leonel Pacha
 Practico: 3
 Objetivo: Estudiar las llamadas getpid() y getppid().
 Fecha: 25/03/2020
\**************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	
	int pid, pid2, ppid;
	
	pid = fork();
	
	if (pid != 0) {
		
		printf("Soy el proceso padre");
		
		pid2 = getpid();
		
		ppid = getppid();		//obtengo el ID del proceso padre en ejecucion
		
		printf(" Mi ID de proceso es %d y el ID de mi padre es %d\n", pid2, ppid);
		
	} else {
		
		printf("Soy el proceso hijo");		
		
		pid2 = getpid();
		
		ppid = getppid();
		
		printf(" Mi ID de proceso es %d y el ID de mi padre es %d\n", pid2, ppid);
		
	}
		
	return 0;
}