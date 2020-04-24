#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

int main() {

	DIR *dir;
   dir = opendir("/");
	struct dirent *diren;

	if ((dir == NULL) {
		printf("No se pudo abrir el directorio");
		exit(1);
	}

	while ((diren = readdir(dir)) != NULL) {
		printf("%s\n", diren->d_name);
   }

   closedir(dir);

   return 0;

}