#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h> 
#include <time.h>
#include <stdbool.h>
int main() {
	int tube, tamBuffer=24;
	char * mififo = "./mififo";
	mkfifo(mififo, 0666);
	time_t curtimeA;
	time(&curtimeA);
	tube = open(mififo, O_WRONLY);	
	write(tube, ctime(&curtimeA), tamBuffer);
	close(tube);
	unlink(mififo);
	return 0;
}
