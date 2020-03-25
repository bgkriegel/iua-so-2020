/**************************************************************\
 Autor: Eliana Cano
 Practico: 7
 Objetivo: Crear un programa que cree un hijo y manejar señales.
 Fecha: 22/03/2020
\**************************************************************/

//Cuando presiono ctrl-z la señal es manejada por interumpir() y se finaliza el programa. No sé 
//cómo finalizar solo el hijo (para que el padre sea el que termine el programa cuando termine el hijo)

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

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

int main() {

    int pid;
    int mi_pid;
    int status = 0;

    pid = fork();

    if ( pid == 0 ) {
        /* estoy en hijo */
        printf("Soy el hijo");
        mi_pid = getpid();
        printf(" mi PID es %d \n", mi_pid);
            signal (SIGINT, interrumpir); //la señal la manejará interrumpir()
            signal (SIGTSTP, suspender); //la señal la manejará suspender()
            sleep(5);  
            exit(3);
        
        //cuando le envio una señal a este proceso para que termine, el estado de salida es 15, y WIFEXITED retorna false
        
    } else {
         /* estoy en padre */
        wait(&status); //espera a que termine el proceso hijo
        
        if (WIFEXITED(status)) {
            printf("Soy el padre");
            mi_pid = getpid();
            printf(" mi PID es %d \n", mi_pid);
            printf("Mi hijo terminó con un estado: %d \n", status);
            WEXITSTATUS(status);
        } else {
            printf("Ocurrió un error en la espera \n");
            printf("Estado de salida: %d \n", status);
            return -1;
        }
        
    }

    return 0;
}
