/**************************************************************\
 Autor: Ivan Guerra
 Practico: 3
 Objetivo: Finalizar un programa utilizando el contenido de un archivo externo. 
 Escribir un programa similar al ejercicio 1, pero ahora se debe leer el contenido del archivo. 
 Si contiene un valor '1' entonces prosigue. 
 Si contiene el valor '0' termina.
 Fecha: 25/04/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_BYTES 1
#define NUMBER_ONE '1'
#define NUMBER_ZERO '0'

int main(int argc, char *argv[])
{
  char *filename;
  char buff[MAX_BYTES];

  if (argc != 2)
  {
    printf("Uso: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Archivo de origen
  filename = argv[1];

  // Abro el archivo 'filename' y obtengo su descriptor de archivo
  int fd = open(filename, O_RDONLY);

  if (fd < 0)
  {
    printf("Hubo un error al abrir el archivo '%s'\nSaliendo del programa...\n", filename);
    exit(EXIT_FAILURE);
  }

  while ( 1 ) {
    printf("Estoy esperando un valor '0' ó '1' en el archivo '%s'...\n", filename);

    read(fd, buff, MAX_BYTES);
    sleep(3);

    if (*buff == NUMBER_ONE) {
        printf("\nSe encontro el valor %s en el archivo...\nSe prosigue con la ejecucion del programa...\n\n", buff);
    }
    if (*buff == NUMBER_ZERO) {
        printf("\nSe encontro el valor %s en el archivo...\nSaliendo del programa...\n", buff);
        sleep(3);
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);
    fd = open(filename, O_RDONLY);

    if (fd < 0)
    {
        printf("Hubo un error al abrir el archivo '%s'\nSaliendo del programa...\n", filename);
        exit(EXIT_FAILURE);
    }
  }

  return EXIT_SUCCESS;
}