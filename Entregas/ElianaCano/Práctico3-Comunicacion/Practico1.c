/**************************************************************\
 Autor: Eliana Cano
 Practico: 3
 Objetivo: Finalizar un programa utilizando un archivo externo
 Fecha: 06/04/2020
\**************************************************************/

//Escriba un programa que verifique periódicamente la
//existencia de un archivo (elija el nombre)
//Si descubre que existe entonces termina.

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main () {

int fd;
int i = 0;

printf("Hola \n");

while (i >= 0) {

    fd = open ("test.txt", O_RDONLY);

    if (fd != -1) {
        printf ("******Saliendo... OPEN retornó %d (iteración %d)****** \n", fd, i+1);
        exit(1);
    }

    printf ("Me sigo ejecutando.... Iteración %d", i+1);
    sleep(i+1);
    i++;
}

return 0;

}