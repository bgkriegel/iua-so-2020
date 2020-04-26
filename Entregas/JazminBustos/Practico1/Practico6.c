#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal Handler for SIGINT
void signalTerminate(int sig_num)
{
	printf("\n Este proceso no se puede terminar con Ctrl+C. \n");

	// Reset handler to catch SIGINT next time
	signal(SIGINT, signalTerminate);
	fflush(stdout);
}

// Signal Handler for SIGTSTP
void signalSuspend(int sig_num)
{
	printf("\n Este proceso se termina con Ctrl+Z. \n");
	exit(0);
}

int main()
{
	signal(SIGINT, signalTerminate);
	signal(SIGTSTP, signalSuspend);

	// Infinite loop
	while (1) {
	}
	return 0;
}
