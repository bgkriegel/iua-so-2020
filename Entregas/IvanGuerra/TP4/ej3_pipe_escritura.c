/**************************************************************\
 Autor: Ivan Guerra
 Practico: 4
 Objetivo: Cliente-Servidor con pipes con nombre.
  - Escribir dos programas que se comunicaran utilizando pipes con nombre.
  - El primer programa obtiene la hora del sistema y la imprime en el stdout.
  - Luego, el segundo leera desde el stdout y mostrara el contenido por pantalla.
  - En el medio, estos programas se comunicaran mediante un pipe con nombre.
 Fecha: 11/05/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main() {
  char *currentTime;
  time_t curtime;

  time(&curtime);
  currentTime = ctime(&curtime);

  write(1, currentTime, strlen(currentTime)-1);

  return EXIT_SUCCESS;
}