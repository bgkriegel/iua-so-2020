#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>

int main(){

	DIR *directorio;
	struct dirent *dirDirent;
	int numFiles = 0;

	directorio = opendir("/");

	if(directorio == NULL){
		printf("No se puede ingresar al directorio\n");
		exit(0);
	} else {
		printf("Usted esta en el directorio raiz\n");
		printf("Contenido del directorio:\n");

		while((dirDirent  = readdir(directorio))){
			numFiles = numFiles + 1;
			printf("Archivo numero %d : %s\n", numFiles, dirDirent -> d_name);
		}

		closedir(directorio);
	}

	return 0;	

}