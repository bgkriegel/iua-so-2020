#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h> 
#include <time.h>
#include <stdbool.h>
int main() {
	int tube, tamBuffer=24;
	char * mififo = "./mififo";
	tube = open(mififo, O_RDONLY);
	unsigned char bufferBB[tamBuffer];
	read(tube, bufferBB, tamBuffer);
	for(int j=0; j<tamBuffer; j++){
		printf("%c",bufferBB[j]);
	}
	printf("\n");
	close(tube);
	return 0;
}
