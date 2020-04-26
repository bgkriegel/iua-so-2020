#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
int main(int argc, char *argv[]) {
	int fil;
	do{
		fil=open("test.txt",O_RDONLY);
		fil=close(fil);
	}while(fil>=0);
	
	printf("esto se va a cerrar\n");
	return 0;
}
