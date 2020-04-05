/**************************************************************\
 Autor: Ivan Guerra
 Practico: 2
 Objetivo: Escribir un programa que reciba por linea de comando el nombre de un archivo 
 y lo copie en un archivo con la extension '.bak'. 
 Usar open(), close(), read() y write().
 Fecha: 02/04/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_BYTES 2

int main(int argc, char *argv[])
{
  int fdSrcFile, fdDstFile;
  char *srcFilename, *dstFilename;
  char *dstFileExtension = ".bak";
  char buff[MAX_BYTES];
  int nBytesRead;

  if (argc != 2)
  {
    printf("Uso: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Archivo de origen
  srcFilename = argv[1];

  // Abro el archivo 'srcFilename' en modo LECTURA y obtengo su descriptor de archivo
  fdSrcFile = open(srcFilename, O_RDONLY);

  if (fdSrcFile < 0)
  {
    printf("Hubo un error al abrir el archivo de origen '%s'", srcFilename);
    exit(1);
  }

  // Archivo de destino (Su nombre es igual al archivo de origen + la extension '.bak')
  dstFilename = strcat(strtok(srcFilename, "."), dstFileExtension);

  // Abro el archivo 'dstFilename' en modo LECTURA Y ESCRITURA, y ademas si no
  // existe, se crea el archivo, y ademas limpia todo el contenido inicial que tenga si existe
  // y obtengo su descriptor de archivo
  // Ademas, obtengo el descriptor de archivo y le indico permisos de rw para el dueño, y solo lectura para cualquier otro.
  fdDstFile = open(dstFilename, O_RDWR | O_CREAT | O_TRUNC, 0644);

  if (fdDstFile < 0)
  {
    printf("Hubo un error al abrir el archivo de destino '%s'", dstFilename);
    exit(1);
  }

  // int read(int fd, void *buf, size_t count);
  // Leo desde el descriptor de archivo 'fdSrcFile' una cantidad 'MAX_BYTES' y lo guardo en buff.
  // 'n' retorna el numero de bytes leidos o cero si llego al fin del archivo.
  nBytesRead = read(fdSrcFile, buff, MAX_BYTES);

  if (nBytesRead == 0) // Archivo vacio.
  {
    printf("*** Archivo de origen vacio. ***\n");
    exit(0);
  }
  else
  {
    // Escribo el contenido leido del archivo de origen que esta almacenado en el buffer 'buff' en el archivo de destino.
    write(fdDstFile, buff, MAX_BYTES);

    // Recorro y leo el descriptor de archivo 'fd' mientras 'n' retorne valores positivos
    while ((nBytesRead = read(fdSrcFile, buff, MAX_BYTES)) != 0)
    {
      // Cuando el valor de 'n' sea menor a 'MAX_BYTES' estoy en la ultima seccion del archivo
      // y debo dejar de leer y salir del loop.
      if (nBytesRead < MAX_BYTES)
      {
        printf("Fin de la escritura.\n");
        break;
      }

      write(fdDstFile, buff, MAX_BYTES);
    }
  }

  // Cierro el descriptor de archivo del archivo de origen
  close(fdSrcFile);
  // Cierro el descriptor de archivo del archivo de destino
  close(fdDstFile);

  return 0;
}
