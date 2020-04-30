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
#include <sys/wait.h>
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
  int fdSon = open(filename, O_RDWR | O_TRUNC, 0644);
  int fdFather = open(filename, O_RDONLY);

  if (fdFather < 0)
  {
    printf("Hubo un error al abrir el archivo '%s'\nSaliendo del programa...\n", filename);
    exit(EXIT_FAILURE);
  }

  int pid;
  // int status;
  pid = fork();

  if (pid == -1)
  {
    printf("Error al crear el proceso hijo\n");
    return 1;
  }

  if (pid == 0)
  {
    // Proceso hijo (Nuevo proceso creado)
    int i = 0;
    while ( 1 )
    {
      if (i < 10) {
        printf("\nSoy el proceso B y en %d segundos escribrire el valor '%s' en el archivo '%s'..\n", (10-i), "1", filename);
      }

      if (i == 10) {
        write(fdSon, "1", MAX_BYTES);
        printf("\nSoy el proceso B y acabo de escribir el valor '%s' en el archivo '%s'..\n", "1", filename);
        close(fdSon);
      }

      if (i > 10 && i < 20) {
        printf("\nSoy el proceso B y en %d segundos escribrire el valor '%s' en el archivo '%s'..\n", (20-i), "0", filename);
      }

      if (i == 20) {
        fdSon = open(filename, O_RDWR | O_TRUNC, 0644);
        write(fdSon, "0", MAX_BYTES);
        printf("\nSoy el proceso B y acabo de escribir el valor '%s' en el archivo '%s'..\n", "0", filename);
        close(fdSon);
        exit(EXIT_SUCCESS);
      }

      sleep(1);
      i++;
    }
  }
  else
  {
    // Proceso padre (Proceso que creo el nuevo proceso)
    while ( 1 ) {
      printf("\nSoy el Proceso A... y estoy esperando un valor '0' ó '1' en el archivo '%s'...\n", filename);

      read(fdFather, buff, MAX_BYTES);
      sleep(3);

      if (*buff == NUMBER_ONE) {
          printf("\nSe encontro el valor %s en el archivo...\nSe prosigue con la ejecucion del programa...\n\n", buff);
      }
      if (*buff == NUMBER_ZERO) {
          printf("\nSe encontro el valor %s en el archivo...\nSaliendo del programa...\n", buff);
          sleep(3);
          close(fdFather);
          exit(EXIT_FAILURE);
      }

      close(fdFather);
      fdFather = open(filename, O_RDONLY);

      if (fdFather < 0)
      {
          printf("Hubo un error al abrir el archivo '%s'\nSaliendo del programa...\n", filename);
          exit(EXIT_FAILURE);
      }
    }
  }

  // Limpiar el archivo
  fdSon = open(filename, O_RDWR | O_TRUNC, 0644);
  close(fdSon);

  return EXIT_SUCCESS;
}