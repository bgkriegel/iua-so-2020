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
char buff = 1;
char val;
int n = 1;
//size_t  bytes;

printf ("Crearé el archivo, soy el proceso A. Ingresar el mensaje a escribir. \n");

    fd = open ("test3.txt", O_CREAT);
    scanf("%s",&val);
    if (write(fd,&val,1)) {
        printf("Escribí un %s en el archivo \n", &val);
        close(fd); 
    } else {
        printf ("Error al escribir en el archivo destino. \n");
        perror("Error de escritura");
        }

    //Usaré sleep para que el proceso A le de tiempo al proceso B a que escriba el archivo

while (n!=0) {

    sleep (n);
    printf ("Esperando... \n");

    fd = open ("test3.txt", O_RDONLY);
    
    read (fd, &buff, 1);

    close (fd);

    if (val == buff) {
        printf ("El mensaje ha sido modificado, finalizaré.");
        exit (0);
    }

    n++;
}

return 0;

}


