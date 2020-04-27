/**************************************************************\
 Autor: Eliana Cano
 Practico: 4
 Objetivo: Comunicar dos procesos a través de una tubería sin nombre.
 Fecha: 26/04/2020
\**************************************************************/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

/*Cliente-Servidor con pipes sin nombre. Escribiremos un programa que
creara dos hijos los cuales se comunicaran utilizando pipes sin nombre.
Uno de los hijos obtiene la hora del sistema como antes, y envía ese dato
utilizando pipes. El segundo recibe los datos y los muestra por pantalla.*/

int main () {

    int pid1, pid2, pd[2];
    pipe (pd);
    char buff;
    time_t actual = time(NULL);

    pid1 = fork();
    if (pid1 == 0) {

        buff = ctime(&actual);
        write (pd[0], &buff, sizeof(buff));
        exit(0);
    }

    pid2 = fork();

    if (pid2 == 0) {

        char buff2;

        read (pd[1], &buff2, sizeof(buff));
        printf("%d \n", buff2);

    }

    return 0;
    
}