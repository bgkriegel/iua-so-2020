#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

	int pid, pidMuestra, pidPadre;

	pid = fork();

	if(pid == 0){
		pidMuestra = getpid();
		pidPadre = getppid();
		printf("Yo soy un hijo. Mi numero Id = %d y el Id de mi padre es: %d\n",
			pidMuestra,pidPadre);
	} else {
		pidMuestra = getpid();
		printf("Yo soy un padre. Mi numero Id: %d\n",pidMuestra);
	}

	return 0;

}