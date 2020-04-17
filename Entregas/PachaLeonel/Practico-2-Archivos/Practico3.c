/**************************************************************\
 Autor: Leonel Pacha
 Practico: 3
 Objetivo: Leer directorios.
 Fecha: 10/04/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main () {
	
	DIR * pun_dir = opendir("/");
	
	//DIR es un tipo de dato que representa un directorio, en este caso un puntero a directorio
	//la funcion opendir() tiene como argumento al directorio que se quiere abrir
	//Devuelve un puntero del directorio (DIR) o NULL en caso de error.
	
	struct dirent * dirent_pun;
	
	//la struct dirent representa la siguiente entrada de directorio al que apunte cuando use readdir()
	/*Esta contiene: d_name --> nombre de los directorios o archivos que contiene
					 d_type --> tipo de archivo (directorio o archivo)
					 entre otras*/
	
	if (pun_dir == NULL){
		printf("No se logro abrir el directorio\n");
		exit(1);
	}
	
	do {
		
		printf("%s\n", dirent_pun -> d_name);
		
	} while ((dirent_pun = readdir(pun_dir)) != NULL);
	
	closedir(pun_dir);	
	
	/*La función closedir() cierra el flujo de directorio que se obtuvo con opendir. 
	Recibe como parámetro el puntero al directorio y devuelve 0 en caso de éxito y -1 en caso de error.*/
	
    return 0;
}