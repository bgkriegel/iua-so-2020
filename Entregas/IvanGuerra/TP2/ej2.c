/**************************************************************\
 Autor: Ivan Guerra
 Practico: 2
 Objetivo: Genere un archivo que contenga un listado extendido del contenido 
 del directorio raiz (/). Escriba un programa que lea dicho archivo y muestre su contenido 
 en pantalla. Para ello use las llamadas al sistema open(), close() y read().
 Fecha: 01/04/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FILENAME "test_ej2.txt"
#define MAX_BYTES 4

int main()
{
  // Abro el archivo 'FILENAME' y obtengo su descriptor de archivo
  int fd = open(FILENAME, O_RDONLY);
  char buff[MAX_BYTES];

  if (fd < 0)
  {
    printf("Hubo un error al abrir el archivo '%s'", FILENAME);
    exit(1);
  }

  // int read(int fd, void *buf, size_t count);
  // Leo desde el descriptor de archivo 'fd' una cantidad 'MAX_BYTES' y lo guardo en buff.
  // 'n' retorna el numero de bytes leidos o cero si llego al fin del archivo.
  int n = read(fd, buff, MAX_BYTES);

  if (n == 0) // Archivo vacio.
  {
    printf("*** Archivo vacio. ***\n");
    exit(0);
  }
  else
  {
    // Imprimo el contenido del buffer
    printf("%s", buff);

    // Recorro y leo el descriptor de archivo 'fd' mientras 'n' retorne valores positivos
    while ((n = read(fd, buff, MAX_BYTES)) != 0)
    {
      // Cuando el valor de 'n' sea menor a 'MAX_BYTES' estoy en la ultima seccion del archivo
      // y debo dejar de leer y salir del loop.
      if (n < MAX_BYTES)
      {
        printf("\n");
        break;
      }
      printf("%s", buff);
    }
  }

  // Cierro el descriptor de archivo
  close(fd);

  return 0;
}