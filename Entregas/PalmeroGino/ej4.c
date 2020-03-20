#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
void salidelhijo(int *estado){
	if(WIFEXITED(*estado))
		printf("proceso hijo terminado \n");
	else
		printf("proceso hijo en ejecucion \n");

}
int main() {
	int pid, padrePid, estado;
	pid = fork();

	if (pid == 0) {
		salidelhijo(&estado);
		printf("soy el hijo %d, mi hijo es: %d, mi padre es: %d\n", getpid(), pid, getppid());

	} else {
		wait(&estado);
		salidelhijo(&estado);
		printf("soy el padre %d, mi hijo es: %d, mi padre es: %d\n", getpid(), pid, getppid());
		
	}
	return 0;
	}
