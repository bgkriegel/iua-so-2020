/**************************************************************\
 Autor: Leonel Pacha
 Practico: 6
 Objetivo: Manejo de señales de procesos.
 Fecha: 25/03/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void manejadorSenial (int numsig) {			//manejo la señal
	
	if (numsig == SIGINT){		//el numero de interrupcion de señal es 2
	
		printf("Acaba de interrumpir el proceso :(, recibi la señal: %d\n", numsig);
	
		fflush(stdout);
		
		/*Todos los caracteres que se envian a la shell, no se envian a esta directamente, en 
		su lugar se almacenan en un bufer y se almacenan ahi hasta ser vaciado, esto es, 
		mover los caracteres del bufer a la shell u otra salida... por lo tanto, fflush() 
		vacia el bufer*/
		
		/*Al usar la señal de interrumpir, esta se deja de captar desde el main() porque ya la use,
		entonces se debe instanciar nuevamente la señal para ser usada de nuevo...
		en el caso de suspender, no hace falta ya que el proceso termina*/
		
		signal (SIGINT, manejadorSenial);
		
		return;
		
	} else if (numsig == SIGTSTP) {			//el numero de suspension es 18 | 20 | 24
		
		printf("Va a suspender el proceso :( ... recibi la señal: %d\n", numsig);
		
		exit(0);
		
	}
	
}

int main() {
	
	signal (SIGINT, manejadorSenial);
	
	signal (SIGTSTP, manejadorSenial);
	
	/*Instancio cada señal que usare, en una manejo la de suspender y en la otra la de interrumpir*/
	
	int i = 1;
	
	while (i != 0) {	
			
			printf("Repeticion %d\n", i);
			
			sleep(i);
			
			i++;
			
	}
	
	return 0;
}