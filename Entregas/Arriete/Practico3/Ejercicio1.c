#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

	int fd;
	int i =1;

	while(i > 0){
		if(i == 5){
		
			fd = open("archivoAbrir.txt", O_RDONLY|O_CREAT);

		} else {

			fd = open("archivoAbrir.txt", O_RDONLY);

		}

		if (fd == -1)
		{
			printf("El archivo se mantiene cerrado, abra el archivo 'archivoAbrir'\n");
			sleep(1);
		} else {
			printf("El archivo se ha abierto en la interacion: %d\n", i);
			exit(1);
		}

		i++;


	}


	return 0;

}
