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
	int filA=open("a-inout", O_CREAT, 0644);
	filA=close(filA);
	int filB=open("b-inout", O_CREAT, 0644);
	filB=close(filB);
	hijoA = fork();
	hijoB = fork();
	if (hijoA == 0&& hijoB!=0) {
		int archBA=open("b-inout", O_RDWR|O_CREAT, 0644);
		time_t curtimeA;
		time(&curtimeA);
		write(archBA, ctime(&curtimeA), tamBuffer);
		archBA=close(archBA);
		estadoA=false;
	}else if(hijoB == 0&& hijoA!=0){
		int archBB=open("b-inout", O_RDONLY);
		unsigned char bufferBB[tamBuffer];
		read(archBB, bufferBB, tamBuffer);
		for(int j=0; j<tamBuffer; j++){
			printf("/%c",bufferBB[j]);
		}
		printf("\n");
		archBB=close(archBB);
		estadoB=false;
	} else if(hijoB != 0&& hijoA!=0){
		sleep(3);
		printf("Ambos procesos terminaron perfectamente\n");
	}
}
