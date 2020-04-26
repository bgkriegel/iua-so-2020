/**************************************************************\
 Autor: Ivan Guerra
 Practico: 3
 Objetivo: Finalizar un programa utilizando un archivo externo. 
 Escribir un programa que verifique periódicamente la existencia de 
 un archivo (se debe poder elegir el nombre).
 Si se descubre que existe, entonces el programa termina.
 Fecha: 25/04/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char *filename;

  if (argc != 2)
  {
    printf("Uso: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Archivo de origen
  filename = argv[1];

  // Abro el archivo 'filename' y obtengo su descriptor de archivo

  int fd = open(filename, O_RDONLY);

  while (fd < 0) {
    printf("Estoy esperando la existencia del archivo '%s'...\n", filename);
    sleep(3);

    fd = open(filename, O_RDONLY);
    close(fd);
  }

  printf("\nSe encontro el archivo '%s'...\nSaliendo del programa...\n", filename);
  sleep(3);

  return EXIT_SUCCESS;
}