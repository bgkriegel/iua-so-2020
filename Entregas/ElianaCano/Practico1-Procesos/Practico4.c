/**************************************************************\
 Autor: Eliana Cano
 Practico: 4
 Objetivo: Estudiar la llamada wait().
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

    pid = fork();

    if ( pid == 0 ) {
        /* estoy en hijo */
        printf("Soy el hijo");
        mi_pid = getpid();
        printf(" mi PID es %d \n", mi_pid);
        sleep(2);
        exit(3); //el proceso hijo termina normalmente
        
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
            return -1;
        }
        
    }

    return 0;
}