/**************************************************************\
 Autor: Eliana Cano
 Practico: 3
 Objetivo: Comunicar dos procesos a través de un archivo.
 por otro proceso.
 Fecha: 12/04/2020
\**************************************************************/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main () {

int fd;
int i = 0;
char val;

while (i >= 0) {

    fd = open ("test3.txt", O_RDONLY);

    printf ("Soy el proceso B, encontré el archivo.");

    close (fd);

    printf ("Ingresar el mensaje a escribir. \n");

    fd = open ("test3.txt", O_WRONLY);
    scanf("%s",&val);
    if (write(fd,&val,2)) {
        printf("Escribí un %s en el archivo \n", &val);
        close(fd); 
        exit(0);
    } else {
        printf ("Error al escribir en el archivo destino. \n");
        perror("Error de escritura");
        }

    sleep(i);
    i++;
}

return 0;

}