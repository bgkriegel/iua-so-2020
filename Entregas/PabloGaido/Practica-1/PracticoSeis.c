#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>



int main()
{
	int status;
	int pid, my_pid;
	pid = fork();
	int hijo = 0;

	if (pid == 0) {
		hijo = getpid();		// returns the process ID (PID) of the calling process.
		printf("Proceso Hijo, mi PID es %d\n", hijo);
		my_pid = getppid();		// returns the process ID of the parent of the calling process.
		printf("el PID de mi padre es %d\n", my_pid);

		//sleep for 5 seconds
    		sleep(5);

 		//exit with statys 12
    		exit(12);


	} else {


		 //waiting for child to terminate
    		pid = wait(&status);

		 kill(hijo, SIGKILL);

   		if ( WIFEXITED(status) ){
      		printf("Parent: Child exited with status: %d\n", WEXITSTATUS(status));
    		}

		my_pid = getpid();
		printf("Proceso Padre, mi PID es %d\n", my_pid);



	}
	return 0;
}
