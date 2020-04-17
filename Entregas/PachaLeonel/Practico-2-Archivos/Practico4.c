/**************************************************************\
 Autor: Leonel Pacha
 Practico: 4
 Objetivo: Generar una copia de respaldo de un archivo.
 Fecha: 10/04/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main (int args, char *argv[]) {

    if (args != 2){
		printf("ERROR = No se ingreso bien el nombre del archivo\n");
		exit(1);
	}

    int filedesc, filedesc2;
	char buffer[200];
	ssize_t bytes = 1, bytes1 = 1;
	
	filedesc = open(argv[1], O_RDONLY);
	filedesc2 = open("backup.bak", O_RDWR|O_CREAT, 0644);		//acceso de lectura y escritura; si no exite, lo crea
	/*El tercer argumento son las flags de modo del archivo (archivo o carpeta, read, write, exe)*/	
	
	if (filedesc == -1 || filedesc2 == -1){
		printf("ERROR = No se pudieron crear / abrir los archivos\n");
		exit(1);
	}
	
	while (bytes > 0){
		
		bytes = read (filedesc, buffer, 150);
		
		printf(" ___________________________ Lei %ld Bytes ___________________________\n", bytes);
		
		// if (bytes > 0)
			// printf("%s", buffer); //imprimo lo que acabo de leer	

		bytes1 = write(filedesc2, buffer, bytes);
		/*La funcion write(int fd, const void *buf, size_t count) escribe la cantidad de bytes
		del buffer en el archivo referido al filedesc
		Retorna el valor de bytes escritos, en caso de error es -1*/
		
		if (bytes1 == bytes)
			printf("Realizando copia de seguridad del archivo\n");
		
		if (bytes1 == -1){
			printf("ERROR = No se puede realizar la copia de seguridad\n");
			exit(1);
		}
		
	}	//Leo hasta que se termine el archivo (EOF)
	
	printf("------------------- FIN DE LA COPIA DE SEGURIDAD ------------------\n");
	
	close(filedesc);
	close(filedesc2);
	
    return 0;
}