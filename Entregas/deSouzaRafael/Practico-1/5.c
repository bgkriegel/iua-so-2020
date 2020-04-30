#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid, status;

    pid = fork();

    if (pid == 0) {
	
        printf("I'm the child. My ID is %d and my father's ID is %d\n", getpid(), getppid());
		
			int i=1;
			
			while (1) {
			printf("Iteration: %d", i);
			i++;
			sleep(4);
			}
		
    } else {
		
		wait(&status);
	
		if (WEXITSTATUS(status)){
			
			printf("I'm the father. My ID is %d and my son finished with the status: %d\n", getpid(),status);
			
		}
			
		}else{
			printf("Error.\n");
			exit(1);
		}
    }
    return 0;
}