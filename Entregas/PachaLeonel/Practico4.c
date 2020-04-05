/**************************************************************\
 Autor: Leonel Pacha
 Practico: 4
 Objetivo: Estudiar la llamada wait().
 Fecha: 25/03/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	
	int pid, pid2, status;
	
	pid = fork();
	
	if ( pid == 0 ) {		//si estoy en el hijo...
	
		printf("Soy el proceso hijo");		
		
		pid2 = getpid();
		
		printf(" Mi ID de proceso es %d\n", pid2);
		
		/*Aca necesito algo que frize la pantalla para que lo pueda visualizar, uso la funcion
		sleep() para eso, duerme o retrasa por una cantidad de segundos... el wait() 
		se utiliza para esperar que un proceso finalice*/
		
		sleep(2);
		
		exit(3); 
		
		/*El exit() hace que el proceso termine normalmente y el valor de status y 0xff, 
		es retornado al padre*/
	
	} else {		//estaria en el padre
	
		wait(&status);		//Aqui espero que el hijo termine
		
		if (WIFEXITED(status)) {		//retorna verdadero si el hijo finalizo correctamente
		
			printf("Soy el proceso padre");
		
			pid2 = getpid();
		
			printf(" Mi ID de proceso es %d\n", pid2);
			
			printf(" Mi hijo finalizo con un estado: %d\n", status);
			
			WEXITSTATUS(status);		
			
			/*Si el valor de WIFEXITED no es cero, evalúa los 8 bits de orden inferior del 
			argumento de estado que el proceso hijo pasó a exit () */
		
		} else {			//si el hijo no finalizo bien
		
			printf("Ocurrio un error en la espera del proceso\n");
			
			return -1;			//Para mostrar que el programa termino mal, se usa -1 y para bien, 0
		
		}	
	
	}
	
	return 0;
}