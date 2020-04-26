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

int pid;

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
	
	int status;
	
	pid = fork();
	
	if ( pid == 0 ) {		
	
		printf("Soy el proceso hijo, Mi ID de proceso es %d\n", getpid());		

        signal (SIGINT, manejadorSenial);
	
	    signal (SIGTSTP, manejadorSenial);
		
		sleep(4);
			
		exit(3);
	
	} else {		
	
		wait(&status);		
		
		if (WIFEXITED(status)) {

			kill(pid, SIGKILL);
		
			printf("Soy el proceso padre,  Mi ID de proceso es %d\n", getpid());
			
			signal (SIGINT, manejadorSenial);
	
			signal (SIGTSTP, manejadorSenial);
			
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
