/**************************************************************\
 Autor: Leonel Pacha
 Practico: 1
 Objetivo: Cliente-Servidor con archivos y tuberias.
 Fecha: 26/04/2020
\**************************************************************/

/*Cliente-Servidor con archivos. Exploraremos la posibilidad de "comunicar" 
dos procesos mediante archivos externos. Escriba un programa que "cree" dos
archivos, a-inout y b-inout. Luego deberá crear dos hijos, cada hijo deberá 
abrir los archivos PERO de modo que el primer hijo abra "a" para lectura y 
"b" para escritura, en cambio el segundo abrira "a" para escritura y "b"
para lectura. Una vez realizado esto el primer hijo debera obtener la hora
del sistema (usando ctime()), escribira esta informacion en "b", cuando esto
ocurra, el segundo proceso hijo obtendra a su vez la hora y la leerra de 
"b", y la mostrara por pantalla. Al finalizar ambos procesos hijos
el padre deberá reportar el estado de terminacion.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main () {
	
	int pid1, pid2, filedesc1, filedesc2, status;
	char buffer, buffer1;
	time_t timeact;
	
	filedesc1 = creat("a-inout.txt", 0644);
	filedesc2 = creat("b-inout.txt", 0644);
	
	pid2 = fork();
	
	if (pid1 == 0) {
		
		printf("Soy el proceso hijo 1, mi ID de proceso = %d, el ID de mi padre = %d\n", getpid(), getppid());
		
		filedesc1 = open("a-inout.txt", O_RDONLY);
		filedesc2 = open("b-inout.txt", O_WRONLY);
		
		time(&timeact);
		buffer = ctime(&timeact);
	
		write (filedesc2, &buffer, sizeof(buffer));
		
		close(filedesc1);
		close(filedesc2);
		
		exit(0);
		
	}
	
	pid1 = fork();
	
	if (pid2 == 0) {
		
		printf("Soy el proceso hijo 2, mi ID de proceso = %d, el ID de mi padre = %d\n", getpid(), getppid());
		
		filedesc1 = open("a-inout.txt", O_WRONLY);
		filedesc2 = open("b-inout.txt", O_RDONLY);
		
		read(filedesc2, &buffer1, sizeof(buffer1));
		
		printf("%s\n", buffer1);
		
		close(filedesc1);
		close(filedesc2);
		
		exit(0);
		
	} else {
		
		wait(&status);		
		
		if (WIFEXITED(status)) {		
		
			printf("Soy el proceso padre, mi ID es = %d\n", getpid());
			
			printf(" Mi hijo finalizo con un estado: %d\n", status);
			
			WEXITSTATUS(status);		
		
		} else {			
		
			printf("Ocurrio un error en la espera del proceso\n");
			
			return -1;			
			
		}	
	}
	
	return 0;
	
}