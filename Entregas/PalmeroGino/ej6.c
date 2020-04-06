#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void interrumpir (int sig_num) {
    printf("Proceso interrumpido. Señal nro: %d \n", sig_num);
    signal (SIGINT, interrumpir); //Hace que la señal SIGINT siga siendo manejada por interrumpir() y no por la funcion "por defecto"
    fflush(stdout);
    return;
}

void suspender (int sig_num) {
    printf("Proceso suspendido. Señal nro: %d \n", sig_num);
    exit(0);
}

int main () {

    signal (SIGINT, interrumpir); //la señal SIGINT realizara interrumpir()
    signal (SIGTSTP, suspender); //la señal SIGINT realizara suspender()

    for(int i = 1; i>0; i++){ 
        printf("Iteracion numero: %d \n", i);
        sleep(i);
    }

}
