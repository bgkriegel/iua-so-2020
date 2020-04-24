/**************************************************************\
 Autor: Eliana Cano
 Practico: 3
 Objetivo: Finalizar un programa dependiendo del contenido de un archivo, que es controlado
 por otro proceso.
 Fecha: 06/04/2020
\**************************************************************/

//Si el archivo contiene un 1--->Se sigue ejecutando
//Si el archivo contiene un 0--->Finaliza al proceso B, y se finaliza a sí mismo también


#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main () {

int fd;
int i = 0;
char buff = 2;
int pid;
int status;
char val;
//size_t  bytes;

pid = fork();

if (pid == 0) {

    printf ("Escribiré el archivo, soy el proceso hijo. Ingresar 1 o 0 \n");

        fd = open ("test.txt", O_WRONLY);
        scanf("%s",&val);
        if (write(fd,&val,1)) {
            printf("Escribí un %s en el archivo \n", &val);
            close(fd); 
        } else {
            printf ("Error al escribir en el archivo destino. \n");
            perror("Error de escritura");
            }
    } else {
            wait(&status);
            printf ("Soy el proceso padre. Procederé a leer el archivo... \n");
            fd = open ("test.txt", O_RDONLY);

            while (i >= 0) {

                read (fd, &buff, 1);

                if (buff == '0') {
                    printf ("******Saliendo... (iteración %d)****** \n", i+1);
                    exit(1);
                } else if (buff == '1') {
                    printf ("Me sigo ejecutando.... Iteración %d \n", i+1);
                } else {
                    printf ("El caracter leído no es 0 ni 1, me sigo ejecutando :) \n");
                }
                sleep(i+1);
                i++;
                }
            }
return 0;

}