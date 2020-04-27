#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void signalI(int sig){
	printf("Signal iterrupted. Signal: %d\n", sig);
	signal(SIGINT, signalI);
	fflush(stdout);
}

void signalS(int sig){
	printf("Signal suspended. \n");
	exit(0);
}

int main() {

	signal(SIGINT, signalI);
	
	signal(SIGSTOP, signalS);
	
	while (1) {
	}
	return 0;
}

int main() {
    int pid, status=0;

    pid = fork();

    if (pid == 0) {
	
        printf("I'm the son. My ID is %d and my father's ID is %d\n", getpid(), getppid());
		signal(SIGINT, signalI);
		signal(SIGSTOP, signalS);
		sleep(3);
		exit(11);
		
    } else {
		
		wait(&status);
	
		if (WEXITSTATUS(status)){
			printf("I'm the father. My ID is %d and my son finished with the status: %d\n", getpid(),status);
			WEXITSTATUS(status);
		}else{
			wait(&status);
			printf("Error.\n");
			exit(1);
		}
    }
    return 0;
}