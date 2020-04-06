/**************************************************************\
 Autor: Eliana Cano
 Practico: 3
 Objetivo: Finalizar un programa dependiendo del contenido de un archivo.
 Fecha: 06/04/2020
\**************************************************************/

//Si el archivo contiene un 1--->Se sigue ejecutando
//Si el archivo contiene un 0--->Finaliza

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main () {

int fd;
int i = 0;
char buff = 2;
//size_t  bytes;

while (i >= 0) {

    fd = open ("test.txt", O_RDONLY);

    read (fd, &buff, 1);

    printf ("Linea leida... \n");

    if (buff == '0') {
        printf ("******Saliendo... OPEN retornó %d (iteración %d)****** \n", fd, i+1);
        exit(1);
    } else if (buff == '1') {
        printf ("Me sigo ejecutando.... Iteración %d \n", i+1);
    } else {
        printf ("El caracter leído no es 0 ni 1, me sigo ejecutando :) \n");
    }
    sleep(i+1);
    i++;
}

return 0;

}