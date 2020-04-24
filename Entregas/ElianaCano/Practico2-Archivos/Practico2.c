/**************************************************************\
 Autor: Eliana Cano
 Practico: 2
 Objetivo: Leer archivos.
 Fecha: 05/04/2020
\**************************************************************/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main () {

int fd; //file descriptor
char buff [200];
ssize_t  bytes = 1; //para que no sea = 0

fd = open("out.txt", O_RDONLY); //Abro el archivo solo para lectura. Devuelve -1 si no se pudo abrir.

//read retorna -1 en caso de error, por lo cual hay que monitorear este valor en cada lectura

if (fd == -1) {
    printf ("Error al abrir el archivo.");
    exit (1);
}

while (bytes > 0) {
    bytes = read (fd, buff, 150);
    if (bytes > 0)
    printf( "%s", buff);
    
} //leer hasta que se llegue al EOF (final del archivo), es decir, hasta que el número de bytes leídos sean 0.
printf ("*******************Fin de la lectura****************************");

close (fd);

return 0;

//No sé por qué el programa lee una línea más, aunque ya haya terminado el archivo.Ya sé--> eliminar \n y el printf de bytes. Hice las correcciones y sigue mostrando una línea de más

}