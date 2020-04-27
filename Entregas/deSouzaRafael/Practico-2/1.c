#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	
	for (int i = 0; i < argc; i++ ) {
 	  printf("%s \n",argv[i]);
	}

	return 0;
}
