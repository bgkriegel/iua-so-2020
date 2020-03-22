/**************************************************************\
 Autor: Eliana Cano
 Practico: 4
 Objetivo: Estudiar la llamada wait().
 Fecha: 22/03/2020
\**************************************************************/
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

int main() {

    int pid;
    int mi_pid;
    int status = 0;
    int ret;

    pid = fork();

    if ( pid != 0 ) {
        /* estoy en padre */
        ret = wait(&status); //espera a que termine el proceso hijo
        if (ret != -1) {
            printf("Soy el padre");
            mi_pid = getpid();
            printf(" mi PID es %d \n", mi_pid);
            printf("Mi hijo terminó con un estado: %d \n", status);
        } else {
            printf("Ocurrió un error en la espera");
            return -1;
        }

    } else {
        /* estoy en hijo */
        printf("Soy el hijo");
        mi_pid = getpid();
        printf(" mi PID es %d \n", mi_pid);
        
    }

    return 0;
}