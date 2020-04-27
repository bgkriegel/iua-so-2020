/**************************************************************\
 Autor: Leonel Pacha
 Practico: 2
 Objetivo: Cliente-Servidor con tuberias.
 Fecha: 26/04/2020
\**************************************************************/

/*Cliente-Servidor con pipes sin nombre. Escribiremos un programa que
creara dos hijos los cuales se comunicaran utilizando pipes sin nombre.
Uno de los hijos obtiene la hora del sistema como antes, y envía ese dato
utilizando pipes. El segundo recibe los datos y los muestra por pantalla.*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

int main () {

    int pid1, pid2, pd[2];
	
    pipe (pd);
	
    char buffer;
	
    time_t timeact;

    pid1 = fork();
	
    if (pid1 == 0) {
		
		time(&timeact);
		
        buffer = ctime(&actual);
		
        write (pd[0], &buffer, sizeof(buffer));
		
        exit(0);
		
    }

    pid2 = fork();

    if (pid2 == 0) {

        char buffer2;

        read (pd[1], &buffer2, sizeof(buffer));
		
        printf("%d \n", buff2);

    }

    return 0;
    
}