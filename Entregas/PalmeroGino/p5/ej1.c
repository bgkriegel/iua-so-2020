#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h> 
#include <time.h>
#include <stdbool.h>
#include <semaphore.h>
bool salidelhijo(int *estado){
	return WIFEXITED(*estado);
}
sem_t semaforillo;
int main() {
	int hijoA, hijoB, estadoA, estadoB, tamBuffer=24;
	sem_init(&semaforillo, 0, 1); //0 indica que se va a trabajar con hilos internos; 1 indica el tamanio del semaforo(antes de entrar en accion)
	hijoA = fork();
	hijoB = fork();
	if (hijoA == 0&& hijoB!=0) {
		int numero;
		salidelhijo(&estadoA);
		for(int i=0;i<10;i++){
			numero = rand() % (2+1);
			sem_wait(&semaforillo);
			printf("Produciendo %d\n",i);
			sleep(numero);
			sem_post(&semaforillo);
		}
		return 0;
	}else if(hijoB == 0&& hijoA!=0){
		int numeroB;
		salidelhijo(&estadoB);
		for(int i=0;i<10;i++){
			numeroB = rand() % (3+1);
			sleep(numeroB);
			sem_wait(&semaforillo);
			printf("Consumiendo %d\n",i);
			sem_post(&semaforillo);
		}
		return 0;
	} else if(hijoB != 0&& hijoA!=0){
		wait(&estadoA);
		wait(&estadoB);
		printf("Ambos procesos terminaron perfectamente\n");
		return 0;
	}
}
