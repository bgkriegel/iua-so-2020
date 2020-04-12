/**************************************************************\
 Autor: Leonel Pacha
 Practico: 1
 Objetivo: Mostrar los argumentos de la linea de comandos.
 Fecha: 10/04/2020
\**************************************************************/

#include <stdio.h>

int main (int args, char *argc[]) {

    /*args es la cantidad de elementos de la linea de comandos
    argc[] es el arreglo que contiene cada elemento...
    ejemplo: ./Practico1 "hola mundo"   imprime:
    ./Practico1
    hola mundo*/

    for (int i = 0; i < args; i++) 
        printf("%s \n", argc[i]);

    return 0;
}