#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main () {
   
   sysyem("cd");
   system("touch prueba.txt");
   system("ls -l ./* > prueba.txt");

   int fd;
   char buffer[20000];
   ssize_t bytes = 1;

   fd = open("prueba.txt", O_RDONLY);

   if (fd == -1)
   {
      printf("No se pudo abrir el archivo");
      exit(1);
   }

   while (bytes > 0)
   {
      bytes = read(fd,buffer, 400);
      printf("bytes = %ld \n", bytes);
      if(bytes > 0) {
         printf("%s \n", buffer);
      }
   }

   close(fd);
   return 0;

}