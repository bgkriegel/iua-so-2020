#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int int main() {

   int pid1, pid2, pid3, pd[2];
   pid1 = fork();

   pipe(pd;
   
   char buf[256]) =  {'E','l',' ','m','e','n','s','a','j','e'};

   if (pid2 == 0)
   {
      printf("soy el hijo uno, mi poadre es: %d, mi pid= %d\n", getppid(), getpid());
      close(pd[0]);
      write(pd[1], buff, strlen(buf));
      close(pd[1]);
      return 0;
   }

   pid3 = fork();

   if(pid3 == 0) {
      char buf[256];
      printf("soy el hijo dos, mi padre es: %d, mi pid es: %d\n", getppid(), getpid());
      sleep(1);
      close(pd[1]);
      read(pd[0], buf, 256);
      close(pd[0]);
      printf(buf);
   }

   printf("soy el provceso padre: %d\n", getpid());
   return 0;
}