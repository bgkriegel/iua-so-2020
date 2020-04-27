#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


int int main() {

   int fileD;
   int i;
   char valor;
   
   while (1)
   {
      fileD = open("comunicador.txt", O_RDONLY);
      printf("Aca el proceso B\n");
      close(fileD);

      printf("Ingresar el mensaje: ");

      fileD = open("comunicador.txt", O_WRONLY);
      scanf("%s", &valor);

      if(write(fileD, &valor, 2))
      {
         printf("Archivo escrito: %s\n", &val);
         close(fileD);
         exit(0);
      } else
      {
         perror("error al escribir el mensaje");
      }
      sleep(5);
   }
    return 0;
}