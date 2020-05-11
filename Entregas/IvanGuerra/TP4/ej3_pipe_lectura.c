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

int main() {
  int n;
  char buff[24];

  if (( n = read( 0, buff, sizeof(buff)) ) > 0) {
    printf("El valor leido del pipe es: %s\n", buff);
    exit( EXIT_SUCCESS );
  }

  exit( EXIT_FAILURE );
}