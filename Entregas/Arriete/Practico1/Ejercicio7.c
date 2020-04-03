#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>


void signalSuspend(int sig_num){
	printf("Para rehabilitar el proceso ingrese fg en la consola\n");
	signal(SIGINT, signalSuspend);
	fflush(stdout);
	return;
}

void signalTerminate(int sig_num){
	printf("El proceso se esta cerrando. \n");
	exit(0);
}

int main()
{
	int pid, pidMuestra, pidPadre, status;

	pid = fork();

	if (pid == 0)
	{
		pidMuestra = getpid();
		pidPadre = getppid();
		printf("Yo soy un hijo. Mi numero Id = %d y el Id de mi padre es: %d\n",
			pidMuestra,pidPadre);
			signal(SIGINT, signalTerminate);
			signal(SIGTSTP, signalSuspend);
		sleep(4);

		exit(5);
		
	} else {
		if(pid > 0){
			wait(&status);
			if(WIFEXITED(status)){
				pidMuestra = getpid();
				printf("Yo soy un padre. Mi numero Id = %d, y mi hijo ha finalizado en un estado = %d\n",
				pidMuestra,WEXITSTATUS(status));

			}
		}
	}

	while (1) {
		kill(pid, 10);
	}
	return 0;


}