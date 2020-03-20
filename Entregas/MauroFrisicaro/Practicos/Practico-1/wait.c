/* 4. Escriba un programa en el cual creamos un proceso y configuramos
   al proceso “padre” para que espere, por medio de la llamada wait(),
   a que termine su hijo antes de proseguir, luego de lo cual debe
   reportar el status de salida del proceso hijo.
   Use la llamada wait(). Se la debe invocar como:

   ...
   wait(&STATUS);
   ...

   Use el status de salida, analícelo por medio de las funciones macro
   definidas en la página de manual de la llamada wait().

   5. Escriba un programa similar al anterior, pero modificado de modo
   que el hijo quede en espera indefinida, luego desde una terminal envíe
   una señal (por medio del comando kill para que termine y observe el
   comportamiento del status de salida.
   Investigue las señales posibles por medio de man 7 signal. */

#include <stdio.h>

int main()
{
	int pid, my_pid;
	pid = fork();

	if (pid != 0) {
		my_pid = getpid();
		printf("Proceso Padre, mi PID es %d\n", my_pid);
		wait(&status);
	} else {
		my_pid = getpid();
		printf("Proceso Hijo, mi PID es %d\n", my_pid);
	}
	return 0;
}


