/**************************************************************\
 Autor: Ivan Guerra
 Practico: 2
 Objetivo: Escriba un programa que muestre en orden todos los argumentos pasados 
 por linea de comando.
 Fecha: 01/04/2020
\**************************************************************/

#include <stdio.h>

int main(int argc, char *argv[])
{
  for (int i = 0; i < argc; i++)
  {
    printf("Argumento #%d => %s\n", (i + 1), argv[i]);
  }
}