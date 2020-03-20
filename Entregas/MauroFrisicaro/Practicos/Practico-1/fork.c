/* 2. Escriba un programa (en C) que utilice la llamada fork() para
   crear un nuevo proceso. Es necesario que cada proceso escriba un
   mensaje diferente en pantalla.
*/

#include <stdio.h>
// #include <sys/types.h>
// #include <unistd.h>

int main()
{
	int pid, my_pid;
	pid = fork();

	if (pid == 0) {
		my_pid = getpid();
		printf("Proceos Hijo, mi PID es %d\n", my_pid);
	} else {
		my_pid = getpid();
		printf("Proceso Padre, mi PID es %d\n", my_pid);
	}
	return 0;
}
