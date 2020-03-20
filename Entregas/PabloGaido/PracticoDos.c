#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

    int pid;
    int mi_pid;

    pid = fork();

    if ( pid != 0 ) {
        /* estoy en padre */
        printf("Soy el padre");
        mi_pid = getpid();
        printf(" mi PID es %d\n", mi_pid);
    } else {
        /* estoy en hijo */
        printf("Soy el padre");
        mi_pid = getpid();
        printf(" mi PID es %d\n", mi_pid);
    }

    return 0;
}
