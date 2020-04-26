#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
int main(int argc, char *argv[]) {
	system("ls -l > test.txt");
	int fil=open("test.txt",O_RDONLY), bytes_read;
	int tam = 10;
	unsigned char buffer[tam];
	do {
		bytes_read = read(fil, buffer, tam);
		for(int i=0; i<bytes_read; i++) {
            		printf("%c", buffer[i]);
        	}
	}while(bytes_read!=0);
	fil=close(fil);
}
