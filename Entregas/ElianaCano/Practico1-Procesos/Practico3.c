/**************************************************************\
 Autor: Eliana Cano
 Practico: 3
 Objetivo: Estudiar las llamadas getpid() y getppid().
 Fecha: 22/03/2020
\**************************************************************/
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

int main() {

    int pid;
    int mi_pid;
    int mi_ppid;

    pid = fork();

    if ( pid != 0 ) {
        /* estoy en padre */
        printf("Soy el padre");
        mi_pid = getpid();
        mi_ppid = getppid();
        printf(" mi PID es %d y el PID de mi padre es %d\n", mi_pid, mi_ppid);
    } else {
        /* estoy en hijo */
        printf("Soy el hijo");
        mi_pid = getpid();
        mi_ppid = getppid();
        printf(" mi PID es %d y el PID de mi padre es %d\n", mi_pid, mi_ppid);
    }

    return 0;
}
