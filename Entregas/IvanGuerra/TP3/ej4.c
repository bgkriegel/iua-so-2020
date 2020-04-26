/**************************************************************\
 Autor: Ivan Guerra
 Practico: 4
 Objetivo: Intercambio de mensajes entre dos procesos utilizando un archivo. 
 Sean dos procesos, A y B, los cuales van a 'hablar'. 
 - A crea un archivo, ej. comunicador.txt, y escribe dentro de el un mensaje. 
 Luego lee periodicamente el archivo y espera que el mensaje 'cambie', 
 cuando descubre que ha cambiado termina. 
 - B verifica que exista el archivo anterior, cuando lo encuentra lo lee, 
 luego lo sobre-escribe con un mensaje de respuesta, cierra el archivo y termina.
 Fecha: 25/04/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define mensaje_proceso_A "Este es un mensaje desde el proceso A."
#define mensaje_proceso_B "Esta es la respuesta desde el proceso B."

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

  int pid;
  pid = fork();

  if (pid == -1)
  {
    printf("Error al crear el proceso hijo\n");
    return 1;
  }

  if (pid == 0)
  {
    // Proceso hijo (Nuevo proceso creado)
    int fd;

    fd = open(filename, O_RDWR);

    if (fd >= 0) {
      remove(filename);
    }

    fd = open(filename, O_RDWR);

    while (fd < 0) {
      printf("\nSoy el proceso B... y estoy esperando la existencia del archivo '%s'...\n", filename);
      sleep(2);
      close(fd);
      fd = open(filename, O_RDWR);
    }

    fd = open(filename, O_RDWR | O_TRUNC, 0644);
    write(fd, mensaje_proceso_B, sizeof(mensaje_proceso_B)-1);
    close(fd);

    printf("\n-------------------------------------------------------------------------------------\n");
    printf("Soy el proceso B... y acabo de escribir una respuesta en el archivo '%s'\nTerminando el proceso B...\n", filename);
    printf("-------------------------------------------------------------------------------------\n");

    exit(EXIT_SUCCESS);
  }
  else
  {
    // Proceso padre (Proceso que creo el nuevo proceso)
    int fd;
    int i=0;
    char buff_mensaje_A[100];

    while ( i <= 10 ) {
      if (i < 10) {
        printf("Soy el Proceso A... y en %d segundos crearé un archivo con el nombre '%s'\n", (10-i), filename);
      }

      if (i == 10) {
        fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);

        if (fd < 0)
        {
          printf("Hubo un error al abrir el archivo '%s'\nSaliendo del programa...\n", filename);
          exit(EXIT_FAILURE);
        }

        write(fd, mensaje_proceso_A, sizeof(mensaje_proceso_A)-1);
        close(fd);

        printf("\n----------------------------------------------------------------------------------\n");
        printf("Soy el proceso A... y acabo de escribir un mensaje en el archivo '%s'\n", filename);
        printf("----------------------------------------------------------------------------------\n\n");

        break;
      }

      sleep(1);
      i+=1;
    }

    int n;
    while ( 1 ) {
      fd = open(filename, O_RDONLY);

      printf("Soy el Proceso A... y estoy esperando un cambio en el contenido del archivo '%s'\n", filename);
      sleep(2);

      n = read(fd, buff_mensaje_A, 100);
      close(fd);

      if ((strcmp(buff_mensaje_A, mensaje_proceso_A) != 0) || (n != sizeof(mensaje_proceso_A)-1)) {
        printf("\n-------------------------------------------------------------------------------------\n");
        printf("Soy el Proceso A... y detecté un cambio en el contenido del archivo '%s'\nTerminando el proceso A...\n", filename);
        printf("-------------------------------------------------------------------------------------\n\n");
        sleep(2);
        
        break;
      }

      buff_mensaje_A[0] = 0;
    }
  }

  return EXIT_SUCCESS;
}