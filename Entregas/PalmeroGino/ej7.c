#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

int padrePid, pid;


void interrumpir (int sig_num) {
	if (pid == 0) {
		printf("Proceso hijo interrumpido. Señal nro: %d\n", sig_num);
	} else {
		printf("Proceso padre interrumpido. Señal nro: %d\n", sig_num);
	}
	signal (SIGINT, interrumpir); //Hace que la señal SIGINT siga siendo manejada por interrumpir() y no por la funcion "por defecto"
	fflush(stdout);
	return;
}
void salidelhijo(int *estado){
	if(WIFEXITED(*estado))
		printf("proceso hijo terminado \n");
	else
		printf("proceso hijo en ejecucion \n");

}

void hijoTermino (int sig_num) {
	printf("Proceso hijo suspendido. Señal nro: %d\n", sig_num);
	system("kill" + getpid());
	printf("Como el proceso hijo termino, con la señal nro: %d , terminando el padre.\n", sig_num);
	system("kill" + getppid());
	exit(0);
}

int main() {
	int estado;
	pid = fork(); //crea un hijo
	padrePid=getpid();
	signal (SIGINT, interrumpir); //la señal SIGINT realizara interrumpir()
	if (pid == 0) {
    		signal (SIGTSTP, hijoTermino); //la señal SIGINT realizara suspender()
		salidelhijo(&estado);
		printf("soy el hijo %d, mi hijo es: %d, mi padre es: %d\n", getpid(), pid, getppid());
		sleep(10);
	} else {
		sleep(5);
		printf("soy el padre %d, mi hijo es: %d, mi padre es: %d\n", getpid(), pid, getppid());
	}
	return 0;
}
