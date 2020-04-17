/**************************************************************\
 Autor: Leonel Pacha
 Practico: 5
 Objetivo: Mostrar la informacion de un archivo a partir de la funcion stat().
 Fecha: 10/04/2020
\**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

struct status {
	dev_t		st_dev;		// Identifica el dispositivo que contiene el archivo					
	ino_t		st_ino;		// Numero de serie del archivo
	mode_t		st_mode;	// Tipo de archivo y bits de permiso
	nlink_t		st_nlink;	// Numero de enlaces fisicos
	uid_t		st_uid;		// ID del usuario propietario
	gid_t		st_gid;		// ID del grupo
	dev_t		st_rdev;	// Tipo de dispositivo (si es dispositivo inodo)
	off_t		st_size;	// Tamaño total en bytes
	unsigned long		st_blksize;		// Tamaño de bloque para el sistema de ficheros de E/S
	unsigned long		st_blocks;		// Numero de bloques de disco asignados
	// time_t st_atime;		// Hora ultimo acceso
	// time_t st_mtime;		// Hora ultima modificacion
	// time_t st_ctime;		// Hora ultima modificacion de los atributos
};

//PROBLEMA : sale eeror en compilador en los time_t, como que falta un '.' o ';' o ';' antes de st_ctime

int main (int args, char *argv[]) {

    if (args != 2){
		printf("ERROR = No se ingreso bien el nombre del archivo\n");
		exit(1);
	}

    int filedesc;
	
	struct status stat1;
	
	filedesc = open(argv[1], O_RDONLY);
	
	if (filedesc == -1){
		printf("ERROR = No se puede abrir el archivo\n");
		exit(1);
	}
	
	stat(filedesc, &stat1);	//La funcion stat() se utiliza para devolver información sobre los atributos de un archivo.
	
	printf("%ld\n", stat1.st_size);
	printf("%ld\n", stat1.st_blocks);
	
	close(filedesc);
	
    return 0;
}