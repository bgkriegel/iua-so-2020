#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int int main() {
   int fileD;
	char buffer = 5;

   while (1)
   {
      fileD = open("prueba.txt", O_RDONLY);

      if(fileD == -1 ) {
         perror("No se pudo abrir el archivo");
         exit(1);
      }

      read(fileD, &buffer,1);

      if (buffer == '1')
      {
         printf("En ejecucion \n");
      } else if (buffer == '0')
      {
         printf("Finalizando la ejecucion. 0 encontrado");
         exit(0);
      } else
      {
         printf("No se encontro el 0 en el archivo \n");
      }
      sleep(5);
   }
    return 0;
}