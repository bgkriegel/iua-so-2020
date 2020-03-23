/**************************************************************\
 Autor: Eliana Cano
 Practico: 6
 Objetivo: Capturar señales y manejarlas.
 Fecha: 22/03/2020
\**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void interrumpir (int sig_num) {
    printf("Esto es una interrupción, recibí la señal %d \n", sig_num);
    signal (SIGINT, interrumpir); //para evitar que la proxima vez esta señal sea manejada por defecto, y no por la función interrumpir()
    fflush(stdout);
    return;
}

void suspender (int sig_num) {
    printf("Suspendiendo proceso... recibí la señal %d \n", sig_num);
    exit(0);
}

int main () {

    signal (SIGINT, interrumpir); //la señal la manejará interrumpir()
    signal (SIGTSTP, suspender); //la señal la manejará suspender()

    int i = 1;
    while (i > 0) { 
        printf("Bucle número: %d \n", i);
        sleep(i);
        i++;
    }

}