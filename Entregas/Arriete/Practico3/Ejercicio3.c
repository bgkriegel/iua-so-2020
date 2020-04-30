#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define MAX_BYTES 1 

int main(){

	int fd,i = 0;
	ssize_t escritor/*,lector*/;
	char buff;

	
		printf("Soy el proceso A\n");

		while(1){
			fd = open("archivoVerificar.txt", O_RDONLY|O_CREAT);

			if (fd == -1)
			{
				printf("No se pudo abrir el archivo\n");
				exit(1);
			} else {
				read(fd,&buff,MAX_BYTES);
				if (buff == '1')
				{
					printf("El programa sigue corriendo\n");
					sleep(1);
				} else {
					if (buff == '0')
					{
						printf("El sistema se cerrara.\n");
						exit(1);
					} else {
						printf("El numero ingresado en el archivo debe ser 1 para continuar o 0 para cerrar\n");
						sleep(1);
					}
				}
			}
			
			if (i == 5)
			{
				break;
			}

			i++;
		}

		while(1){

			fd = open("archivoVerificar.txt", O_RDWR|O_CREAT, 0644);

			sleep(1);

			read(fd,&buff,0);
			printf("El archivo sera modificado y luego sera cerrado.\n");
	    	escritor = write(fd, "0", MAX_BYTES);
	    	if(escritor > 0){

		    	printf("El archivo ha sido modificado.\n");
		    	printf("El programa se cerrara.\n");
		    	exit(1);

	    	} else {
	    		printf("El archivo no se pudo modificar.\n");
	    	}

		}
	
	close(fd);
	return 0;

	
}