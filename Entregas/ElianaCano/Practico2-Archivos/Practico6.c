/**************************************************************\
 Autor: Eliana Cano
 Practico: 2
 Objetivo: Copiar un archivo.
 Fecha: 05/04/2020
\**************************************************************/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//recibir nombre del archivo por linea de comando

int main(int argc, char *argv[]) {

    if (argc != 2) {
        perror("Ingresar el nombre del archivo a copiar");
        exit(1);
    }

    int fd; //file descriptor
    int fd2;
    char buff [200];
    size_t  bytes = 1; //para que no sea = 0
    size_t bytes2;

    fd = open(argv[1], O_RDONLY); //abro el archivo obtenido de la línea de comandos
    fd2 = open("destino.bak", O_RDWR|O_CREAT, 0644); //creo o abro el archivo destino

    if (fd == -1) {
    printf ("Error al abrir el archivo de origen. \n");
    exit (1);
    }
    if (fd2 == -1) {
        printf ("Error al abrir el archivo destino. \n");
        exit(2);
    }

while (bytes > 0) {
    bytes = read (fd, buff, 150);
    printf ("--------------------Bytes = %ld  \n", bytes );
    if (bytes > 0)
    printf( "%s \n", buff);
    bytes2 = write(fd2,buff,bytes);
    if (bytes2 == -1) {
        printf ("Error al escribir en el archivo destino. \n");
        perror("Erro de escritura");
    }
} //leer hasta que se llegue al EOF (final del archivo), es decir, hasta que el número de bytes leídos sean 0.

printf ("*******************Fin de la lectura**************************** \n");

close (fd);
close (fd2);

return 0;

}