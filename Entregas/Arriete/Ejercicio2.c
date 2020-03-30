#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	
	int pid, pidMuestra;

	pid = fork();

	if(pid == 0){
		printf("Yo soy un hijo.\n");
	} else {
		printf("Yo soy un padre.\n");
	}

	return 0;
}