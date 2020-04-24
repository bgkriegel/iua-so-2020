#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


#define MAX_BYTES 4

int main(){

	system("cd");				
	system("touch Archivo.txt");	
	system("ls -l / > Archivo.txt");
	
	int fd = open("Archivo.txt", O_RDONLY);
	char buff[MAX_BYTES];

	

	if (fd < 0)
	{
	  printf("Hubo un problema al intentar abrir el archivo '%s'", "Archivo.txt");
	  exit(1);
	}

	int n = read(fd, buff, MAX_BYTES);

	if (n == 0) // Archivo vacio.
	{
	  printf("*** Archivo vacio. ***\n");
	  exit(0);
	}
	else
	{
	    
	  printf("%s", buff);
	    while ((n = read(fd, buff, MAX_BYTES)) != 0)
	    {
	      if (n < MAX_BYTES)
	      {
	        printf("\n");
	        break;
	      }
	      printf("%s", buff);

	    }
	  }

	  close(fd);

	  return 0;

}