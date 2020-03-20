/* 6. Escriba un programa que capture las señales “Ctrl-C” (Interrumpir) y “Ctrl-Z” (Suspender),
   en el primer caso el programa debe escribir un mensaje en pantalla, en el segundo debe terminar.

   Utilice el siguiente procedimiento: defina una función que retorne void para manejar la señal y
   asigne una señal a esta función por medio de la llamada signal():

    void sigmanager(int sig_num) {
    	    // Reasignar la señal
	    signal(SIGNAL, sigmanager):
	    ...
	    fflush(stdout);
	    }
	    ...
	    signal(SIGNAL, sigmanager);*/

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
