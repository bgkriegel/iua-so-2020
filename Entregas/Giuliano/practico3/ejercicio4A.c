#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int int main() {
    
    int fileD;
    char buff = 1;
    char valor;

    printf("creando archivo del proceso A\n");
    fileD = open("comunicador.txt", O_CREAT);
    printf("Escriba algo en el archivo: ");
    scanf("%s", &valor);
    if(write(fileD,&valor,1)) {
       printf("Se escribio el archivo");
       close(fileD);
    } else {
       perror("Error al escribir el archivo");
    }

    while (1)
    {
      sleep(5);

      fileD = open("comunicador.txt", O_RDONLY);
      read(fileD, &buff,1);
      close(fileD);
      if(valor == buff)  {
         printf("Mensaje modificado con exito");
         exit(0);
      }
    }
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}