#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int pid, my_pid;
	int status;
	pid = fork();

	if (pid == 0) {
		my_pid = getpid();		// returns the process ID (PID) of the calling process.
		printf("Proceso Hijo, mi PID es %d.\n", my_pid);
		my_pid = getppid();		// returns the process ID of the parent of the calling process.
		printf("el PID de mi padre es %d.\n", my_pid);
		sleep(2);
		exit(12);
	} else {
		my_pid = wait(&status);
		printf("Proceso Padre, mi PID es %d.\n", my_pid);
	}
	return 0;
}
