/**************************************************************\
 Autor: Eliana Cano
 Practico: 2
 Objetivo: Leer un directorio.
 Fecha: 05/04/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main () {

	DIR * dir_ptr = NULL;
	struct dirent * dirent_ptr;

    dir_ptr = opendir("/"); //abro el directorio raíz

    if (dir_ptr == NULL) {
        printf ("No se pudo abrir el directorio \n");
        exit (1);
    }

    while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
        printf ("%s \n", dirent_ptr -> d_name); //imprime el nombre del archivo en el directorio
    }

    closedir (dir_ptr);

    return 0;
}