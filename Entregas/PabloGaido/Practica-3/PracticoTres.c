#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>





int main()
{
	int fd;
	ssize_t nr_bytes;
	char buf[10];
	int pid;
	pid = fork();
	if (pid == 0) {
		fd = open("texto.txt", O_RDONLY);	//  "O_RDONLY" me indica que solo hago lectura
		if (fd == -1) {

		printf("Error ar leer el archivo");
		exit(1);

		} else {
		nr_bytes = read(fd, &buf, 1);	//Extraigo el contenido de "texto.txt"
		close((int) fd);
		
		int aux = buf + 0;
		if(aux == '0')
		return 0;
		
	}


	} else {

		sleep(5);
		fd = open("texto.txt", O_RDONLY);	//  "O_RDONLY" me indica que solo hago lectura
		buf[0] = 0;
		write(fd, buf, 10);
		close((int) fd);

	}
	return 0;
}
