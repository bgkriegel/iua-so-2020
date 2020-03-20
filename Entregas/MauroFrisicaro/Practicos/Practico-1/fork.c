/* 2. Escriba un programa (en C) que utilice la llamada fork() para
   crear un nuevo proceso. Es necesario que cada proceso escriba un
   mensaje diferente en pantalla.

   3. Escriba un programa similar al anterior, de modo que cada proceso
   obtenga su propio numero de proceso y el de su padre; a continuación
   imprima el resultado.
   Estudie y utilice las llamadas getpid() y getppid().
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	int pid, my_pid;
	pid = fork();

	if (pid == 0) {
		my_pid = getpid();		// returns the process ID (PID) of the calling process.
		printf("Proceso Hijo, mi PID es %d\n", my_pid);
		my_pid = getppid();		// returns the process ID of the parent of the calling process.
		printf("el PID de mi padre es %d\n", my_pid);
	} else {
		my_pid = getpid();
		printf("Proceso Padre, mi PID es %d\n", my_pid);
	}
	return 0;
}
