
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	int pid, my_pid;
	
	pid = fork();
	
	if (pid==0) // Este es el proceso padre
	{
		my_pid = getpid();
		printf("Proceso hijo con PID: %d\n", my_pid);
		my_pid = getppid();
		printf("Proceso padre con PID: %d\n", my_pid);
	}
	else // Proceso hijo
	{
		my_pid = getpid();
		printf("Proceso padre con PID: %d\n", getpid());
	}
	return 0;
}
