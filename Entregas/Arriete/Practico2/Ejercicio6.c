#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define MAX_BYTES 1

int main(int argc, char *argv[]){

	int fd, fdNuevo;
	char buff[200];
	ssize_t byte;
	ssize_t byteNuevo;

	fd = open(argv[1], O_RDONLY);
	fdNuevo = open(strcat(argv[1], ".bak"), O_RDWR|O_CREAT, 0644);

	if (fd == -1) {
    printf ("Error al abrir el archivo de origen. \n");
    exit (1);
    } else {
    	if (fdNuevo == -1) {
    	printf ("Error al abrir el archivo de destino. \n");
    	exit (1);
    	} else {
    		byte = read(fd, buff, MAX_BYTES);
    		if(byte == 0){
    			printf("El archivo esta vacio\n");
    			exit(1);
    		}else{
	    		while(byte > 0){

	    			byte =read(fd,buff,MAX_BYTES);

	    			if (byte > 0)
	    			{
	    				byteNuevo = write(fdNuevo, buff, byte);
	    				
	    				if (byteNuevo == -1)
	    				{
	    					printf("No se pudo completar la escritura del archivo\n");
	    				}
	    			}
	    		}

	    		printf("El archivo fue copiado exitosamente con el nombre de %s\n", argv[1]);

	   		}
    	}

	}

	close(fd);
	close(fdNuevo);

	return 0;

}