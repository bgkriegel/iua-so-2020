/*1) Cliente-Servidor con archivos. Exploraremos la posibilidad de "comunicar" 
dos procesos mediante archivos externos. Escriba un programa que "cree" dos
archivos, a-inout y b-inout. Luego deberá crear dos hijos, cada hijo deberá 
abrir los archivos PERO de modo que el primer hijo abra "a" para lectura y 
"b" para escritura, en cambio el segundo abrira "a" para escritura y "b"
para lectura. Una vez realizado esto el primer hijo debera obtener la hora
del sistema (usando ctime()), escribira esta informacion en "b", cuando esto
ocurra, el segundo proceso hijo obtendra a su vez la hora y la leerra de 
"b", y la mostrara por pantalla. Al finalizar ambos procesos hijos
el padre deberá reportar el estado de terminacion.*/


#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	pid_t pid_hijo1, pid_hijo2;


	int pd[2];					/* declaro */
	pipe(pd);					//creo el pipe
	int ainout, binout;


	ainout = creat("a-inout.txt", 0644);	//creo archivo
	binout = creat("b-inout.txt", 0644);	//creo archivo

	pid_hijo1 = fork();			//creo al hijo 2
	if (pid_hijo2 == 0) {
		printf("Soy el hijo 2, Mi padre es= %d, Mi PID= %d\n", getppid(),
			   getpid());

		char buf[256] =
			{ 's', 'o', 'y', ' ', 'a', '-', 'i', 'n', 'o', 'u', 't' };   //inicializo lo que voy a escribir en los archivos
		ainout = open("a-inout.txt", O_WRONLY, 0644);
		binout = open("b-inout.txt", O_WRONLY, 0644);

		write(ainout, buf, strlen(buf));               //escribo en a-inout
		buf[4] = 'b';
		write(binout, buf, strlen(buf));               //escribo en b-inout

		close((int) ainout);
		close((int) ainout);

	}
	pid_hijo2 = fork();			//creo al hijo 1
	if (pid_hijo1 == 0) {
		char buf[256];
		printf("Soy el hijo 1, Mi padre es= %d, Mi PID= %d\n", getppid(),
			   getpid());
		sleep(1);

		ainout = open("a-inout.txt", O_RDONLY, 0644);
		binout = open("b-inout.txt", O_RDONLY, 0644);

		read(ainout, &buf, 256);	//Extraigo el contenido de "a-inout.txt"
		close((int) ainout);
		printf(buf);
		read(binout, &buf, 256);	//Extraigo el contenido de "b-inout.txt"
		close((int) binout);
		printf(buf);


		exit(0);
	}

	sleep(2);

	exit(0);
}
