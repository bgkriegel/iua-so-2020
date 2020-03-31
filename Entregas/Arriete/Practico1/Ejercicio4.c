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
		wait(&status);
		if(WIFEXITED(status)){
			pidMuestra = getpid();
			printf("Yo soy un hijo. Mi numero Id = %d, y mi hijo ha finalizado en un estado = %d\n",
				pidMuestra,status);
			WEXITSTATUS(status);
		} else {

			printf("Un error se ha producido");
			return -1;

		}

	}

	return 0;

}