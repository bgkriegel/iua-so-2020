#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BYTES 1 

int main(){

	int fd;
	int i = 1;
	char buff;

	while(i > 0){

		/*El archivo archivoVerificar se encuentra en blanco debera escribirle un valor*/


		fd = open("archivoVerificar.txt", O_RDONLY);

		if (fd == -1)
		{
			printf("No se pudo abrir el archivo\n");
			exit(1);
		} else {
			if (i == 5)
			{
				
			}
			read(fd,&buff,MAX_BYTES);
			if (buff == '1')
			{
				printf("El programa sigue corriendo\n");
				sleep(1);
			} else {
				if (buff == '0')
				{
					printf("El sistema se cerrara. Numero de interacion:%d\n",i);
					exit(1);
				} else {
					printf("El numero ingresado en el archivo debe ser 1 para continuar o 0 para cerrar\n");
					sleep(1);
				}

				

			}

		}

		i++;


	}

	return 0;

}