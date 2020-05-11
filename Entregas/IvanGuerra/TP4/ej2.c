/**************************************************************\
 Autor: Ivan Guerra
 Practico: 4
 Objetivo: Cliente-Servidor con pipes sin nombre. 
  - Escribir un programa que creara dos hijos los cuales se comunicaran utilizando pipes sin nombre.
  - Uno de los hijos obtiene la hora del sistema como antes, y envía ese dato utilizando pipes. 
  - El segundo recibe los datos y los muestra por pantalla.
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
  char *currentTime;
  time_t curtime;

  pid_t pid1, pid2;

  int pd[2];	/* declaro */
	pipe(pd);		/* creo */

  if ( (pid1 = fork()) == 0 ) { /* primer hijo */
    printf("Soy el primer proceso hijo. Escribiré en el extremo de escritura del pipe.\n");

    close( pd[0] ); /* cierro el extremo de lectura del pipe */
  
    time(&curtime);
    currentTime = ctime(&curtime);

    write(pd[1], currentTime, strlen(currentTime)-1);

    close( pd[1] ); /* cierro el extremo de escritura del pipe */

  } else { /*  padre */
    
    if ( (pid2 = fork()) == 0 ) { /* segundo hijo  */
      printf("Soy el segundo proceso hijo. Leeré en el extremo de lectura del pipe.\n");

      close( pd[1] ); /* cierro el extremo de escritura del pipe */

      int n;

      time(&curtime);
      currentTime = ctime(&curtime);

      char buff[24];

      while (( n = read( pd[0], buff, sizeof(buff)) ) > 0) {
        printf("\nEl valor leido del pipe es: %s\n", buff);
      }
  
      close( pd[0] ); /* cierro el extremo de lectura del pipe */

    } else { /* padre */
      close( pd[0] ); /* cierro el extremo de lectura del pipe */
      close( pd[1] ); /* cierro el extremo de lectura del pipe */
    }

  }

  /* Esperamos al primer hijo */
  waitpid(pid1, NULL, 0);
  /* Esperamos al segundo hijo */
  waitpid(pid2, NULL, 0);

  exit( EXIT_SUCCESS );
}