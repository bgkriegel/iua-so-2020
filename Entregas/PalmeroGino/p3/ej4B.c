#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
int main(int argc, char *argv[]) {
	int fil, bytes_read;
	unsigned char buffer[5];
	do{
		fil=open("test.txt",O_RDONLY);
	}while(fil<0);
	bytes_read = read(fil, buffer, 5);
	for(int i=0; i<bytes_read; i++){
			printf("%c",buffer[i]);
	}
	fil=close(fil);
	fil=open("test.txt", O_RDWR|O_CREAT, 0644);
	unsigned char mensaje[5]={'c', 'h', 'a', 'u', '0'};
	write(fil, mensaje,5);
	fil=close(fil);
	printf("\nesto se va a cerrar\n");
	return 0;

		

	
	
}
