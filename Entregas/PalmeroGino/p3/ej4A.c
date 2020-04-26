#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
int main(int argc, char *argv[]) {
	int tam = 5, bytesToWrite=5;
	
	int filb=open("test.txt", O_RDWR|O_CREAT, 0644);
	unsigned char buffer[5]={'h', 'o', 'l', 'a', '0'};
	write(filb, buffer, bytesToWrite);
	filb=close(filb);
	printf("Archivo escrito con exito\n");
	unsigned char bufferb[5];
	int fil, bytes_read;
	do{
		fil=open("test.txt",O_RDONLY);
		for(int i=0; i<5; i++){
			bytes_read = read(fil, bufferb, 5);
			if(buffer[i]!=bufferb[i]){
				fil=close(fil);
				fil=open("test.txt",O_RDONLY);
				printf("Texto cambiado con el mensaje ");
				bytes_read = read(fil, bufferb, 5);
				for(int j=0; j<5; j++){
					printf("%c",bufferb[j]);
				}
				printf("\nEl programa se va a cerrar\n");
				return 0;
			}
		}
	fil=close(fil);
	}while(fil>=0);
	
	
	exit(EXIT_SUCCESS);
	
}
