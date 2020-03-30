/*7) Escriba un programa que reciba por linea de comando el nombre de
un archivo, a continuacion muestre toda la informacion que se
pueda obtener de ese archivo usando la funcion "stat()".*/



#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <unistd.h>



int main(int argc, char *argv[])
{


	int fd;
	struct stat fileStat;


	 
   	if(stat(argv[1],&fileStat) < 0)    
        return 1;
 
   	 printf("Information for %s\n",argv[1]);
    	 printf("---------------------------\n");
   	 printf("File Size: \t\t%d bytes\n",fileStat.st_size);
    	 printf("Number of Links: \t%d\n",fileStat.st_nlink);
    	 printf("File inode: \t\t%d\n",fileStat.st_ino);
 	printf("File UID: %d\n", fileStat.st_uid);
 
    	 printf("File Permissions: \t");
    	 printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    	 printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
   	 printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    	 printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    	 printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
   	 printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
   	 printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
   	 printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
   	 printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
   	 printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
	 printf("\n\n");
			

	


}
