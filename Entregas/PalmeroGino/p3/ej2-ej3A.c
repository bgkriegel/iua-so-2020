#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
int main(int argc, char *argv[]) {
	int fil, tam = 1, bytes_read;
	unsigned char buffer[tam];
	do{
		fil=open("test.txt",O_RDONLY);
		bytes_read = read(fil, buffer, tam);
		if(buffer[0]=='1')
			fil=close(fil);
		else if(buffer[0]=='0'){
			fil=close(fil);
			printf("Codigo 0, el programa se va a cerrar\n");
			return 0;
		}
		else{
			printf("Problema con el codigo del archivo\n");
			return -1;
		}
	}while(fil>=0);

		

	
	
}
