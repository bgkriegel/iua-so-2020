/**************************************************************\
 Autor: Eliana Cano
 Practico: 4
 Objetivo: Comunicar dos procesos mediante archivos externos.
 Fecha: 26/04/2020
\**************************************************************/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

/*Cliente-Servidor con archivos. Exploraremos la posibilidad de "comunicar" 
dos procesos mediante archivos externos. Escriba un programa que "cree" dos
archivos, a-inout y b-inout. Luego deberá crear dos hijos, cada hijo deberá 
abrir los archivos PERO de modo que el primer hijo abra "a" para lectura y 
"b" para escritura, en cambio el segundo abrira "a" para escritura y "b"
para lectura. Una vez realizado esto el primer hijo debera obtener la hora
del sistema (usando ctime()), escribira esta informacion en "b", cuando esto
ocurra, el segundo proceso hijo obtendra a su vez la hora y la leerra de 
"b", y la mostrara por pantalla. Al finalizar ambos procesos hijos
el padre deberá reportar el estado de terminacion.*/

int main () {

    int fd_a;
    int fd_b;
    int pid;
    int status;
    

    fd_a = open ("a-inout", O_CREAT);
    fd_b = open ("b-inout", O_CREAT);
    close(fd_a);
    close(fd_b);

    pid = fork (); //Creo el primer hijo, que lee a, y escribe b

    if (pid == 0) {

        fd_a = open ("a-inout", O_RDONLY);
        fd_b = open ("b-inout", O_WRONLY);
        
        time_t ahora = time(NULL); // Veo hora actual (en segundos)
        char timec;
        
        timec = ctime (&ahora);

        write (fd_b, &timec, sizeof(timec)); //escribir la hora en b-inout

        close(fd_a);
        close(fd_b);

       // sleep (5);

    }

    pid = fork ();

    if (pid == 0) { //Creo el segundo hijo, que lee b y escribe a

        fd_a = open ("a-inout", O_WRONLY);
        fd_b = open ("b-inout", O_RDONLY);

        char buff;

        read (fd_b, &buff, sizeof(buff)); //leo la hora de b-inout

        printf("%d",buff);

        } else {
            /* estoy en padre */
            wait(&status); //espera a que termine el proceso hijo
        
            if (WIFEXITED(status)) {
                printf("Soy el padre");
                printf("Mi hijo terminó con un estado: %d \n", status);
                WEXITSTATUS(status);
            } else {
                printf("Ocurrió un error en la espera \n");
                printf("Estado de salida: %d \n", status);
                return -1;
            }
        
    }

    }