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
		
		int archAA=open("a-inout", O_RDONLY);
		int archBA=open("b-inout", O_RDWR|O_CREAT, 0644);
		time_t curtimeA;
		time(&curtimeA);
		write(archBA, ctime(&curtimeA), tamBuffer);
		unsigned char bufferAA[tamBuffer];
		read(archAA, bufferAA, tamBuffer);
		for(int j=0; j<tamBuffer; j++){
			printf("\\%c",bufferAA[j]);
		}
		printf("\n");
		archAA=close(archAA);
		archBA=close(archBA);
		estadoA=false;
	}else if(hijoB == 0&& hijoA!=0){
		int archAB=open("a-inout", O_RDWR|O_CREAT, 0644);
		int archBB=open("b-inout", O_RDONLY);
		time_t curtimeB;
		time(&curtimeB);
		write(archAB, ctime(&curtimeB), tamBuffer);
		unsigned char bufferBB[tamBuffer];
		read(archBB, bufferBB, tamBuffer);
		for(int j=0; j<tamBuffer; j++){
			printf("/%c",bufferBB[j]);
		}
		printf("\n");
		archBB=close(archBB);
		archAB=close(archAB);
		estadoB=false;
	} else {
		printf("Ambos");
		while(estadoA==true || estadoB==true){
			printf("Ambos");
			sleep(2);
		}
		printf("Ambos procesos terminaron perfectamente");
	}
}
