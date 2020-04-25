#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
int main(int argc, char *argv[]) {
	int fil=open(argv[1],O_RDONLY), bytes_read;
	char bak[]=".bak";
	char *result = malloc(strlen(argv[1]) + strlen(bak) + 1); // +1 para el "terminar string"
	strcpy(result, argv[1]);
	strcat(result, bak);
	int filbak=open(result, O_RDWR|O_CREAT, 0644);
	int tam = 15;
	unsigned char buffer[tam];
	do {
		bytes_read = read(fil, buffer, tam);
		write(filbak, buffer, bytes_read);
	}while(bytes_read!=0);
	fil=close(fil);
	filbak=close(filbak);
}
