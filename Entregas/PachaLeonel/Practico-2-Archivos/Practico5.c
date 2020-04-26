/**************************************************************\
 Autor: Leonel Pacha
 Practico: 5
 Objetivo: Mostrar la informacion de un archivo a partir de la funcion stat().
 Fecha: 10/04/2020
\**************************************************************/

// struct status {
	// dev_t		st_dev;		// Identifica el dispositivo que contiene el archivo					
	// ino_t		st_ino;		// Numero de serie del archivo
	// mode_t		st_mode;	// Tipo de archivo y bits de permiso
	// nlink_t		st_nlink;	// Numero de enlaces fisicos
	// uid_t		st_uid;		// ID del usuario propietario
	// gid_t		st_gid;		// ID del grupo
	// dev_t		st_rdev;	// Tipo de dispositivo (si es dispositivo inodo)
	// off_t		st_size;	// Tamaño total en bytes
	// unsigned long		st_blksize;		// Tamaño de bloque para el sistema de ficheros de E/S
	// unsigned long		st_blocks;		// Numero de bloques de disco asignados
	// time_t st_atime;		// Hora ultimo acceso
	// time_t st_mtime;		// Hora ultima modificacion
	// time_t st_ctime;		// Hora ultima modificacion de los atributos
// };

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <linux/fs.h>

int main (int args, char *argv[]) {

    if (args != 2){
		printf("ERROR = No se ingreso bien el nombre del archivo\n");
		exit(1);
	}

    int filedesc, sta;
	
	struct stat stat1;
	
	filedesc = open(argv[1], O_RDONLY);		//En el man stat dice que espera como primer argumento un filedescriptor, pero hay que ponerle el nombre del archivo
	
	if (filedesc == -1){
		printf("ERROR = No se puede abrir el archivo\n");
		exit(1);
	}
	
	sta = stat(argv[1], &stat1);	//La funcion stat() se utiliza para devolver información sobre los atributos de un archivo.
	
	if (sta < 0){
		printf("ERROR = No se puede ver las estadisticas del archivo\n");
		exit(1);
	}
	
	printf("Numero de serie del archivo : %ld\n", stat1.st_ino); //
	
	if (S_ISDIR(stat1.st_mode) == S_IFDIR) 
		printf("El archivo es un directirio\n");
	
	if (S_ISCHR(stat1.st_mode) == S_IFCHR) 
		printf("El archivo es un archivo especial (like a terminal)\n");
	
	if (S_ISBLK(stat1.st_mode) == S_IFBLK) 
		printf("El archivo es un archivo de bloques especial (like a disk)\n");
	
	if (S_ISREG(stat1.st_mode) == S_IFREG) 
		printf("El archivo es un archivo regular\n");
	
	if (S_ISFIFO(stat1.st_mode) == S_IFIFO) 
		printf("El archivo es un archivo FIFO especial o una tuberia\n");
	
	if (S_ISLNK(stat1.st_mode) == S_IFLNK) 
		printf("El archivo es un archivo de link simbolico\n");
	
	if (S_ISSOCK(stat1.st_mode) == S_IFSOCK) 
		printf("El archivo es un archivo Socket\n");
		
	printf("Bits de permiso : %#o\n", stat1.st_mode & ~(S_IFMT)); //
	printf("Numero de enlaces fisicos : %ld\n", stat1.st_nlink); //
	printf("ID del usuario propietario : %ld\n", stat1.st_uid); //
	printf("ID del grupo : %ld\n", stat1.st_gid); //
	printf("Tamaño total en bytes : %ld\n", stat1.st_size); //
	printf("Tamaño de bloque para el sistema de ficheros de E/S : %ld\n", stat1.st_blksize); //
	printf("Numero de bloques de disco asignados : %ld\n", stat1.st_blocks); //
	printf("Hora ultimo acceso : %s\n", ctime(&stat1.st_atime)); //
	printf("Hora ultima modificacion : %s\n", ctime(&stat1.st_mtime)); //
	printf("Hora ultima modificacion de los atributos : %s\n", ctime(&stat1.st_ctime)); //
	
	close(filedesc);
	
    return 0;
}