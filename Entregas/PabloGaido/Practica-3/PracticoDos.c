#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>



int main(){

int fd;
int i = 1;
char buf = 2;
ssize_t nr_bytes;


while(i != 0){


fd = open("texto.txt", O_RDONLY);	//  "O_RDONLY" me indica que solo hago lectura


if (fd == -1) {

		printf("Error ar leer el archivo");
		exit(1);

	} else {
		c
		close((int) fd);

		
		if(buf == '0')
		i = 0;
		
	}

}
}
