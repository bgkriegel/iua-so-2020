/*
    Uso de funcion stat()
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int main() {
    struct stat est;
    int fd;
    int st;

    /* Creamos un archivo de prueba */
    fd = open("7-prueba.txt", O_RDWR|O_CREAT, 0644);
    if ( fd < 0 ) {
        printf("Error: no se puede crear el archivo\n");
        exit(1);
    }
    dprintf(fd, "texto de prueba\n");   /* escribimod en file descriptor */
    close(fd);
    /* listo archivo */

    /* Ahora usamos funcion stat() */
    st = stat( "7-prueba.txt", &est );
    if ( st < 0 ) {
        printf("Error: problema al invocar stat()\n");
        exit(2);
    }

    printf("File UID: %d\n", est.st_uid);

    return 0;
}


    

