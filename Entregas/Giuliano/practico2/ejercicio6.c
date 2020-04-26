#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    int fileD1,fileD2;
    char buff [200];
    size_t  bytes = 1; 
    size_t bytes2;

    if (argc != 2) {
        perror("Ingresar el nombre del archivo a copiar");
        exit(1);
    }

    fileD1 = open(argv[1], O_RDONLY); 
    fileD2 = open("destino.bak", O_RDWR|O_CREAT, 0644); 

    if (fileD1 == -1) {
      printf ("Error al abrir archivo. \n");
      exit (1);
    }
    if (fileD2 == -1) {
      printf ("Error al abrir archivo. \n");
      exit(2);
    }

   while (bytes > 0) {
      bytes = read (fileD1, buff, 150);
      printf ("Bytes = %ld  \n", bytes );
      if (bytes > 0) 
         printf( "%s \n", buff);
         
      bytes2 = write(fileD2,buff,bytes);
      if (bytes2 == -1) {
        printf ("Error al escribir en el archivo destino. \n");
        perror("Erro de escritura");
      }
   } 

   close (fileD1);
   close (fileD2);

   return 0;
}