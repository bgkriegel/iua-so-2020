#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h> 
#include <time.h>
#include <stdbool.h>
void salidelhijo(int *estado){
	if(WIFEXITED(*estado))
		printf("proceso hijo terminado \n");
	else
		printf("proceso hijo en ejecucion \n");

}
int main() {
	int hijoA, hijoB, tamBuffer=24;
	bool estadoA = true, estadoB = true;
	int pd[2];
	pipe(pd);
	hijoA = fork();
	hijoB = fork();
	if (hijoA == 0&& hijoB!=0) {
		time_t curtimeA;
		time(&curtimeA);
		write(pd[1], ctime(&curtimeA), tamBuffer);
		estadoA=false;
	}else if(hijoB == 0&& hijoA!=0){
		unsigned char bufferBB[tamBuffer];
		read(pd[0], bufferBB, tamBuffer);
		for(int j=0; j<tamBuffer; j++){
			printf("%c",bufferBB[j]);
		}
		printf("\n");
		estadoB=false;
	} else if(hijoB != 0&& hijoA!=0){
		sleep(5);
		printf("Ambos procesos terminaron perfectamente\n");
	}
}
