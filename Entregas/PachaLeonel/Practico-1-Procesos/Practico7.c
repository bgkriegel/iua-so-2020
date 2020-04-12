/**************************************************************\
 Autor: Leonel Pacha
 Practico: 7
 Objetivo: Observar el manejo de señales de procesos padre e hijo.
 Fecha: 25/03/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/*Escriba un programa que cree un hijo, capture las mismas señales 
del programa anterior, se las reenvie al hijo y reproduzca la 
funcionalidad previa, es decir que el hijo escriba un mensaje para 
la primer señal y termine para la segunda, al terminar el hijo también 
debe terminar el padre.

NO LOGRO HACER QUE EL PADRE SE SIGA EJECUTANDO CUANDO EL HIJO TERMINA, DIRECTAMENTE
SE DEJA DE EJECUTAR TODOOO*/

void manejadorSenial (int numsig) {			
	
	if (numsig == SIGINT){		
	
		printf("Acaba de interrumpir el proceso :(, recibi la señal: %d\n", numsig);
		
		signal (SIGINT, manejadorSenial);

        fflush(stdout);
		
		return;
		
	} else if (numsig == SIGTSTP) {	
		
		printf("Va a suspender el proceso :( ... recibi la señal: %d\n", numsig);
		
		exit(0);
		
	}
	
}

int main() {
	
	int pid, pid2, status;
	
	pid = fork();
	
	if ( pid == 0 ) {		
	
		printf("Soy el proceso hijo");		
		
		pid2 = getpid();
		
		printf(" Mi ID de proceso es %d\n", pid2);

        signal (SIGINT, manejadorSenial);
	
	    signal (SIGTSTP, manejadorSenial);
		
		sleep(4);
			
		exit(3);
	
	} else {		
	
		wait(&status);		
		
		if (WIFEXITED(status)) {		
		
			printf("Soy el proceso padre");
		
			pid2 = getpid();
		
			printf(" Mi ID de proceso es %d\n", pid2);
			
			printf(" Mi hijo finalizo con un estado: %d\n", status);
			
			WEXITSTATUS(status);		
		
		} else {			
		
			printf("Ocurrio un error en la espera del proceso\n");
			
			printf("El estado de salida es: %d\n", status);
			
			return -1;
		
		}	
	
	}
	
	return 0;
}
