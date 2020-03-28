#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	int pid, my_pid;
	pid = fork();

	if (pid == 0) {
		my_pid = getpid();		// returns the process ID (PID) of the calling process.
		printf("Proceso Hijo, mi PID es %d.\n", my_pid);
		my_pid = getppid();		// returns the process ID of the parent of the calling process.
		printf("el PID de mi padre es %d.\n", my_pid);
	} else {
		my_pid = getpid();
		printf("Proceso Padre, mi PID es %d.\n", my_pid);
	}
	return 0;
}
