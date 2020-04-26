/**************************************************************\
 Autor: Leonel Pacha
 Practico: 3
 Objetivo: Finalizar un programa dependiendo del contenido de un 
 archivo, que es controlado por otro proceso.
 Fecha: 10/04/2020
\**************************************************************/

// Si contiene un valor '1' entonces sigue ejecutandose
// Si contiene el valor '0' termina

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main () {
	
	int filedesc, pid, status;
	char buffer = 5, opc;
	
	pid = fork();

	if (pid == 0){
		
		printf("Soy el proceso hijo, voy a escribir en el archivo. Ingrese 1 o 0\n");
		
		scanf("%s", &opc);
		
		filedesc = open ("txt.txt", O_WRONLY);
		
		if (filedesc == -1) { 
			printf("No se pudo abrir el archivo. \n");
			exit(1);
		}
		
		if (write (filedesc, &opc, 1)) { 	//write(int fd, const void *buf, size_t count) escribe count bytes del buffer empezando en buf del archivo referido con fd
			
			printf("Acabo de escribir un %s en el archivo\n", &opc);
			
			close(filedesc);
			
		} else {
			printf("ERROR = No pude escribir en el archivo\n");
			exit(1);
		}
	
	} else {
		
		wait(&status);
		
		printf("Soy el proceso padre, voy a leer el archivo\n");
		
		filedesc = open ("txt.txt", O_RDONLY);
		
		if (filedesc == -1) { 
			printf("No se pudo abrir el archivo. \n");
			exit(1);
		}
		
		while (1) {
		
			read (filedesc, &buffer, 1);	// Le pongo el & ya que espera un puntero
		
			if (buffer == '1') {
				printf ("Sigo ejecutandome...\n");
			} else if (buffer == '0') {
				printf("Oh, encontre el '0' en el archivo\n");
				exit(0);
			} else {
				printf("El archivo contiene otro caracter, por lo tanto no lo reconozco y lo sigo ejecutando :)\n");
			}
		
			sleep(5);
		
		}
		
	}
	
	return 0;
}