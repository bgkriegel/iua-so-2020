/* 6. Escriba un programa que capture las señales “Ctrl-C” (Interrumpir) y “Ctrl-Z” (Suspender),
   en el primer caso el programa debe escribir un mensaje en pantalla, en el segundo debe terminar.

   Utilice el siguiente procedimiento: defina una función que retorne void para manejar la señal y
   asigne una señal a esta función por medio de la llamada signal():

    void sigmanager(int sig_num) {
    	    /* Reasignar la señal *’/
	    signal(SIGNAL, sigmanager):
	    ...
	    fflush(stdout);
	    }
	    ...
	    signal(SIGNAL, sigmanager);

   7. Escriba un programa que cree un hijo, capture las mismas señales del programa anterior,
   se las reenvie al hijo y reproduzca la funcionalidad previa, es decir que el hijo escriba
   un mensaje para la primer señal y termine para la segunda, al terminar el hijo también
   debe terminar el padre. */

