#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h> 
#include <unistd.h>
#include <dirent.h>
int main(int argc, char *argv[]) {
	DIR *carpeta;
	carpeta = opendir("/");
	struct dirent *cosas;
	int cant_archivos=0;
	if(carpeta == NULL)
	{
	    puts("No se pudo abrir el directorio");
	    return(1);
	}
	else
	{
		printf("Nro\tArchivo\t\tTipo\t\tLargo\n");
		while( (cosas=readdir(carpeta)) )
		{
		    cant_archivos++;
		    printf("%d\t %s\t\t%u\t\t%hu\n",
		        cant_archivos,
		        cosas->d_name,
			cosas->d_type,
			cosas->d_reclen
		          );
		}
	}
	closedir(carpeta);

	return(0);
}
