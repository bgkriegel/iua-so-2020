#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

	int pid, pidMuestra, pidPadre, status;

	pid = fork();

	if (pid == 0)
	{
		pidMuestra = getpid();
		pidPadre = getppid();
		printf("Yo soy un hijo. Mi numero Id = %d y el Id de mi padre es: %d\n",
			pidMuestra,pidPadre);

		sleep(4);

		exit(5);
		
	} else {

		kill(pidMuestra, SIGKILL);

		wait(&status);

		if(WIFEXITED(status)){

			pidMuestra = getpid();

			printf("Yo soy un padre. Mi numero Id = %d, y mi hijo ha finalizado en un estado = %d\n",
				pidMuestra,WEXITSTATUS(status));
			
		}

	}

	return 0;

}