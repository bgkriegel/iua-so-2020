#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
int main(int argc, char *argv[]) {
	int tam = 2, bytesToWrite=1;
	unsigned char buffer[tam];
	sleep(3);
	int filb=open("test.txt", O_RDWR|O_CREAT, 0644);
	buffer[0]='0';
	write(filb, buffer, bytesToWrite);
	filb=close(filb);
	printf("Archivo escrito con exito\n");
	exit(EXIT_SUCCESS);
	
}
