#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>





int main()
{
	int fd,aux;
	ssize_t nr_bytes;
	char buf[256];
	int pid;
	pid = fork();
	if (pid == 0) {
			fd = open("texto.txt", O_RDONLY);	//  "O_RDONLY" me indica que solo hago lectura
			if (fd == -1) {

					printf("Error ar leer el archivo, reintentando...");
	
		} else {
			nr_bytes = read(fd, &buf, 256);	//Extraigo el contenido de "texto.txt"
			close((int) fd);
		
			aux = atoi(buf);
			printf("%d\n",aux);		
			if(0 == aux)
			return 0;
		
		}


	} else {

		sleep(5);
		fd = open("texto.txt", O_CREAT | O_TRUNC | O_RDWR, 0644 );	//  "O_RDWR" me indica que es lectura y escritura
		buf[0]='5'; 
		//buf[1]='\0';
		write(fd, buf, strlen(buf));
		close((int) fd);

	}
	return 0;
}