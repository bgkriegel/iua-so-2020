#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++ ) {
 		printf("%s\n",argv[i]);
	}

	return 0;
	}
