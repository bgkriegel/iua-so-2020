#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <linux/fs.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>


	int main(int argc, char *argv[]){

	int fd, verStatus;
	struct tm * time_info_acceso;
	struct tm * time_info_cambio;
	struct tm * time_info_modi;
  	char timeStringAcceso[50];
  	char timeStringCambio[50];
  	char timeStringModi[50];
	struct stat status;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
    	printf ("Error al abrir el archivo de origen. \n");
    	exit (1);
    } else {
    	verStatus = stat(argv[1],&status);
    	if (verStatus < 0)
    	{
    		printf("Hubo un problema al ver el status\n");
    		exit(1);
    	} else {
    		printf("ID del dispositivo que contiene el archivo: Mayor:%d , Menor:%d\n", major(status.st_dev),minor(status.st_dev));

    		printf("Numero de nodo: %ld\n", status.st_ino);

    		/*Reconocimiento tipo de archivo*/
    		if (S_ISREG(status.st_mode))
    		{
    			printf("Tipo del archivo: Es un archivo regular\n");
    		}
    		if (S_ISDIR(status.st_mode))
    		{
    			printf("Tipo del archivo: Es un directorio \n");
    		}
    		if (S_ISCHR(status.st_mode))
    		{
    			printf("Tipo del archivo: Es un dispositivo de caracteres\n");
    		}
    		if (S_ISBLK(status.st_mode))
    		{
    			printf("Tipo del archivo: Es un dispositivo bloqueante\n");
    		}
    		if (S_ISFIFO(status.st_mode))
    		{
    			printf("Tipo del archivo: Es un FIFO\n");
    		}
    		if (S_ISLNK(status.st_mode))
    		{
    			printf("Tipo del archivo: Es un link simbolico\n");
    		}
    		if (S_ISSOCK(status.st_mode))
    		{
    			printf("Tipo del archivo: Es un socket\n");
    		}

    		printf("%#o", status.st_mode & ~(S_IFMT));

    		printf("Sus permisos son: ");

 /*Comienzo reconocimiento permisos usuario*/
    			if (status.st_mode & S_IRUSR)
    				printf("r");
    			else 
    				printf("-");

    			if (status.st_mode & S_IWUSR)
    				printf("w");
    			else 
    				printf("-");

    			if (status.st_mode & S_IXUSR)
    				printf("x");
    			else 
    				printf("-");
/*Fin reconocimiento permisos usuario*/
/*Comienzo reconocimiento permisos grupo*/
    			if (status.st_mode & S_IRGRP)
    				printf("r");
    			else 
    				printf("-");

    			if (status.st_mode & S_IWGRP)
    				printf("w");
    			else 
    				printf("-");

    			if (status.st_mode & S_IXGRP)
    				printf("x");
    			else 
    				printf("-");
/*Fin reconocimiento permisos grupo*/
/*Comienzo reconocimiento permisos otros*/ 
    			if (status.st_mode & S_IROTH)
    				printf("r");
    			else 
    				printf("-");

    			if (status.st_mode & S_IWOTH)
    				printf("w");
    			else 
    				printf("-");

    			if (status.st_mode & S_IXOTH)
    				printf("x");
    			else 
    				printf("-");
/*Fin reconocimiento permisos otros*/

    		printf("\n Numero de enlaces fisicos:%ld\n", status.st_nlink);
    		printf(" ID del usuario propietario:%d\n", status.st_uid);
    		printf(" ID del grupo propietario:%d\n", status.st_gid);
    		printf(" Tipo dispositivo:%ld\n", status.st_rdev);
    		printf(" Tamano total, en bytes:%ld\n", status.st_size);
    		printf(" Tamano de bloque para el sistema de ficheros de E/S:%ld\n", status.st_blksize);
    		printf(" Numero de bloques asignados:%ld\n", status.st_blocks);

			time_info_acceso = localtime(&status.st_atime);
			time_info_modi = localtime(&status.st_mtime);
			time_info_cambio = localtime(&status.st_ctime);
			 
			strftime(timeStringAcceso, sizeof(timeStringAcceso), "%d/%m/%y %H:%M:%S", time_info_acceso);
			strftime(timeStringModi, sizeof(timeStringModi), "%d/%m/%y %H:%M:%S", time_info_modi);
			strftime(timeStringCambio, sizeof(timeStringCambio), "%d/%m/%y %H:%M:%S", time_info_cambio);

    		printf(" Hora del ultimo acceso:%s\n", timeStringAcceso);
    		printf(" Hora del ultimo modificacion:%s\n", timeStringModi);
    		printf(" Hora del ultimo cambio:%s\n", timeStringCambio);
    	}
	}

	return 0;

}


