#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {

	int status;
	int pid, my_pid;
	pid = fork();

	if(pid == 0) { 

		my_pid = getpid();
		printf("Proceso hijo, con PID: %d\n", my_pid);
		
		my_pid = getppid();
		printf("Proceso padre, con PID: %d\n", my_pid);

		sleep(10);

		exit(15);
	} else {
	 
		pid = wait(&status);
		
		if ( WIFEXITED(status) ){
      			printf("Hijo terminado con estatus: %d\n", WEXITSTATUS(status));
    		}

		my_pid = getpid();
		printf("Proceso padre, con PID: %d\n", my_pid);

	}
	return 0;
}
