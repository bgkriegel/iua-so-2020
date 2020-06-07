#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int int main() {
    
    int fileD,aux;
	ssize_t bytes;
	char buf[256];
	int pid = fork();

	if (pid == 0) {
		fileD = open("texto.txt", O_RDONLY);
		if (fileD == -1) {
			perror("Error ar leer el archivo");
            exit(1);
		} else {
			bytes = read(fileD, &buf, 256);
			close(fileD);
			aux = atoi(buf);
			printf("%d\n",aux);		
			if(0 == aux)
			    return 0;
		}
	} else {
		sleep(3);
		fileD = open("texto.txt", O_CREAT | O_TRUNC | O_RDWR, 0644 );
		buf[0]='5';
		write(fileD, buf, strlen(buf));
		close(fileD);
	}
    
	return 0;
}