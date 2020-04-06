/**************************************************************\
 Autor: Eliana Cano
 Practico: 5
 Objetivo: Observar el estado de salida de un proceso que se ejecuta por tiempo indefinido.
 Fecha: 22/03/2020
\**************************************************************/
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    int pid;
    int mi_pid;
    int status = 0;
    int i = 0;

    pid = fork();

    if ( pid == 0 ) {
        /* estoy en hijo */
        printf("Soy el hijo");
        mi_pid = getpid();
        printf(" mi PID es %d \n", mi_pid);
        while (i>=0) { //bucle para que el proceso hijo nunca termine de ejecutarse
            printf("Sigo en el proceso hijo, iteración %d \n", i);
            sleep(5);  
            i++; 
        }
        
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