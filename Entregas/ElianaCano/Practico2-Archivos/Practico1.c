/**************************************************************\
 Autor: Eliana Cano
 Practico: 2
 Objetivo: Mostrar los argumentos ingresados por línea de comando.
 Fecha: 05/04/2020
\**************************************************************/

#include <stdio.h>

int main(int argc, char *argv[])
{
    for (int i=0; i<argc; i++) 
        printf("%s \n", argv[i]);

    return 0;
}