#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int int main() {

   int fileD;
   int i = 1;

   while (i!= 0)
   {
      fileD = open("prueba.txt",O_RDONLY);
      if (fileD==-1)
         sleep(1);
      else
         return 0;  
   }
}