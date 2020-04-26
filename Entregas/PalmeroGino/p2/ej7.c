#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/sysmacros.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h> 
#include <time.h> 
#include <unistd.h>
#include <linux/fs.h>
int main(int argc, char *argv[]) {
	
	struct stat estructura;
	stat(argv[1],&estructura);
	printf("Dispositivo fisico nro:\t%d\n",major(estructura.st_dev));
	printf("Dispositivo logico nro:\t%d\n",minor(estructura.st_dev));
	printf("Inodo:\t%ld\n",estructura.st_ino);
	printf("Proteccion:\t%#o\n",estructura.st_mode & ~(S_IFMT));
	if (S_ISLNK(estructura.st_mode)) {
		printf("Es un vinculo simbolico\n");
	}
	//hacer el resto de los macros
	printf("Enlaces fisicos:\t%ld\n",estructura.st_nlink);
	printf("Owner UID:\t%d\n",estructura.st_uid);
	printf("Owner GID:\t%d\n",estructura.st_gid);
	printf("Tipo inodo:\t%ld\n",estructura.st_rdev);
	printf("Bytes:\t%ld\n",estructura.st_size);
	printf("Bloques para el sistema E/S:\t%ld\n",estructura.st_blksize);
	printf("Bloques asignados:\t%ld\n",estructura.st_blocks);
	printf("Ultimo acceso:\t%s",ctime(&estructura.st_atime));
	printf("Ultima modif.:\t%s",ctime(&estructura.st_mtime));
	printf("Ultimo cambio:\t%s",ctime(&estructura.st_ctime));
	
}
