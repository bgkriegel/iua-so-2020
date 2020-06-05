/**************************************************************\
 Autor: Ivan Guerra
 Practico: 4
 Objetivo: Cliente-Servidor con archivos. 
  - Escribir un programa que "cree" dos archivos, a-inout y b-inout. 
  - Luego deberá crear dos hijos, cada hijo deberá abrir los archivos PERO de modo que 
  el primer hijo abra "a" para lectura y "b" para escritura, en cambio el segundo 
  abrira "a" para escritura y "b" para lectura. 
  - Una vez realizado esto el primer hijo debera obtener la hora del sistema (usando ctime()), 
  escribira esta informacion en "b", cuando esto ocurra, el segundo proceso hijo obtendra 
  a su vez la hora y la leera de "b", y la mostrara por pantalla. 
  - Al finalizar ambos procesos hijos el padre deberá reportar el estado de terminacion.
 Fecha: 11/05/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main() {
  char *filenameA = "a-inout";
  char *filenameB = "b-inout";
  char *currentTime;
  time_t curtime;
  int n;

  pid_t pid1, pid2;
  int status1, status2;


  int fdA = open(filenameA, O_RDWR | O_CREAT | O_TRUNC, 0644);

  if (fdA < 0) {
    printf("Hubo un error al crear el archivo '%s'\nSaliendo del programa...\n", filenameA);
    exit(EXIT_FAILURE);
  }

  close(fdA);

  int fdB = open(filenameB, O_RDWR | O_CREAT | O_TRUNC, 0644);

  if (fdB < 0) {
    printf("Hubo un error al crear el archivo '%s'\nSaliendo del programa...\n", filenameB);
    exit(EXIT_FAILURE);
  }

  close(fdB);

  if ( (pid1 = fork()) == 0 ) { /* hijo */
    fdA = open(filenameA, O_RDONLY);

    if (fdA < 0) {
      printf("Hubo un error al abrir el archivo '%s' en modo lectura.\nSaliendo del programa...\n", filenameA);
      exit(EXIT_FAILURE);
    }

    close(fdA);

    fdB = open(filenameB, O_WRONLY | O_TRUNC, 0644);

    if (fdB < 0) {
      printf("Hubo un error al abrir el archivo '%s' en modo escritura.\nSaliendo del programa...\n", filenameB);
      exit(EXIT_FAILURE);
    }

    time(&curtime);
    currentTime = ctime(&curtime);

    int i = 0;

    while (i < 3) {
      printf("Soy el primer proceso hijo. En %d segundos escribiré el archivo b-inout\n", (3-i));
      sleep(1);
      i++;
    }

    write(fdB, currentTime, strlen(currentTime)-1);

    close(fdB);
  } else { /*  padre */
    
    if ( (pid2 = fork()) == 0 ) { /* segundo hijo  */
      fdA = open(filenameA, O_WRONLY, 0644);
      close(fdA);

      fdB = open(filenameB, O_RDONLY);

      time(&curtime);
      currentTime = ctime(&curtime);

      char buff[24];

      while ( (n = read(fdB, buff, sizeof(buff))) == 0 ) {
        printf("Soy el segundo proceso hijo, y estoy esperando a que se escriba algo en el archivo b-inout\n");
        buff[0] = 0;
        sleep(1);
    
        close(fdB);
        fdB = open(filenameB, O_RDONLY);
      }

      close(fdB);

      fdB = open(filenameB, O_RDONLY);
      buff[0] = 0;
      read(fdB, buff, sizeof(buff));

      printf("\nEl valor leido del archivo b-inout es: %s\n\n", buff);
    } else { /* padre */

      /* Esperamos al primer hijo */
      waitpid(pid1, &status1, 0);
      /* Esperamos al segundo hijo */
      waitpid(pid2, &status2, 0);

      if (WIFEXITED(status1)) {
        printf("El primer proceso hijo termino con normalidad con el estado de salida %d.\n", status1);
        WEXITSTATUS(status1);
      } else {
        printf("Hubo un error. El primer proceso hijo termino con el estado de salida %d (%s).\n", status1, strsignal(status1));
        return -1;
      }

      if (WIFEXITED(status2)) {
        printf("El segundo proceso hijo termino con normalidad con el estado de salida %d.\n", status2);
        WEXITSTATUS(status2);
      } else {
        printf("Hubo un error. El segundo proceso hijo termino con el estado de salida %d (%s).\n", status2, strsignal(status2));
        return -1;
      }

    }

  }

  return EXIT_SUCCESS;
}