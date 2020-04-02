/**************************************************************\
 Autor: Ivan Guerra
 Practico: 2
 Objetivo: Leer el directorio raiz (/) y mostrar su contenido por pantalla. 
 Usar opendir(), readdir() y closedir().
 Fecha: 02/04/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define DIRNAME "."

int main()
{
  DIR *dirp;
  struct dirent *direntp;
  int numOfFiles = 0;

  // abro el directorio
  dirp = opendir(DIRNAME);

  if (dirp == NULL)
  {
    printf("No se puede abrir el directorio.\n");
    exit(1);
  }

  printf("Contenido del directorio '%s'\n", DIRNAME);
  printf("----------------------------\n\n");

  // Leo el contenido del directorio y lo imprimo en pantalla
  while ((direntp = readdir(dirp)))
  {
    numOfFiles++;
    printf("File %d: %s\n", numOfFiles, direntp->d_name);
  }

  printf("\n-----------------------------------\n");
  printf("Fin del contenido del directorio '%s'\n", DIRNAME);

  // Cierro el directorio
  closedir(dirp);

  return 0;
}
