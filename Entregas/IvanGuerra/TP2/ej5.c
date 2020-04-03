/**************************************************************\
 Autor: Ivan Guerra
 Practico: 2
 Objetivo: Escribir un programa que reciba por linea de comando el nombre de un archivo, y 
 a continuacion mostrar toda la informacion que se pueda obtener de ese archivo 
 usando la funcion "stat()".
 Fecha: 02/04/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <sys/sysmacros.h>
#include <string.h>

char *getTimeFormattedToString(time_t time)
{
  struct tm *_time;

  char timeFormattedToString[80];
  char *result;

  _time = localtime(&time);

  strftime(timeFormattedToString, 80, "%d/%m/%Y %H:%M", _time);

  result = timeFormattedToString;

  return result;
}

char *getFileType(mode_t mode)
{
  char *typeInString;
  int typeInOctal = (mode & __S_IFMT);

  switch (typeInOctal)
  {
  case __S_IFBLK:
    typeInString = "Dispositivo de bloque";
    break;
  case __S_IFCHR:
    typeInString = "Dispositivo de caracteres";
    break;
  case __S_IFDIR:
    typeInString = "Directorio";
    break;
  case __S_IFIFO:
    typeInString = "Tuberia con nombre";
    break;
  case __S_IFLNK:
    typeInString = "Enlace simbolico";
    break;
  case __S_IFREG:
    typeInString = "Archivo regular";
    break;
  case __S_IFSOCK:
    typeInString = "Socket";
    break;
  default:
    typeInString = "Desconocido";
    break;
  }

  return typeInString;
}

void printFileProperties(char *filename, struct stat stats)
{

  printf("\nPropiedades del archivo '%s'\n", filename);
  printf("--------------------------------------------------\n\n");

  printf("ID del Dispositivo: major=%d\tminor=%d\n", major(stats.st_dev), minor(stats.st_dev));
  printf("Numero de i-nodo: %ld\n", stats.st_ino);
  printf("Permisos: %#o\n", stats.st_mode & ~(__S_IFMT));
  printf("Tipo de archivo: %s\n", getFileType(stats.st_mode));
  printf("Cantidad de enlaces fisicos: %ld\n", stats.st_nlink);
  printf("ID del usuario propietario: %d\n", stats.st_uid);
  printf("ID del grupo propietario: %d\n", stats.st_gid);

  if (S_ISCHR(stats.st_mode) || S_ISBLK(stats.st_mode))
    printf("Numero del dispositivo (archivo especial): major=%d\tminor=%d\n", major(stats.st_rdev), minor(stats.st_rdev));

  printf("Tamaño total (en bytes): %ld\n", stats.st_size);
  printf("Tamaño de bloque (para el sistema de ficheros de E/S): %ld\n", stats.st_blksize);
  printf("Cantidad de bloques de 512 bytes asignados: %ld\n", stats.st_blocks);
  printf("Hora de ultimo acceso: %s\n", getTimeFormattedToString(stats.st_atime));
  printf("Hora de ultima modificacion: %s\n", getTimeFormattedToString(stats.st_mtime));
  printf("Hora de ultimo cambio: %s\n", getTimeFormattedToString(stats.st_ctime));

  printf("\n---------------------------------------------------");
  printf("\nFin de las propiedades del archivo '%s'\n", filename);
}

int main(int argc, char *argv[])
{
  struct stat stats;
  char *filename;

  if (argc != 2)
  {
    printf("Uso: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Archivo de origen
  filename = argv[1];

  // stat() returns 0 on successful operation,
  // otherwise returns -1 if unable to get file properties.
  if (stat(filename, &stats) == 0)
  {
    printFileProperties(filename, stats);
  }
  else
  {
    printf("No se pueden obtener las propiedades del archivo.\n");
    printf("Verifique si el archivo '%s' existe.\n", filename);
  }

  return 0;
}