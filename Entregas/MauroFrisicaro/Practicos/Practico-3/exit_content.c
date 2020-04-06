/* 2) Finalizar un programa utilizando el contenido de un archivo externo
   Similar al anterior, pero ahora queremos 'ver' que contiene el archivo.
   Si contiene un valor '1' entonces prosigue
   Si contiene el valor '0' termina */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int fd, i = 0;
	char buff = 2;

	printf("Ejecutando...\n");

	while (i >= 0) {
		fd = open("file", O_RDONLY);
		read(fd, &buff, 1);
		printf("Linea leida.\n");

		// Si lee 1 sigue, si lee 0 termina.
		if (buff == '0') {
			printf(">> Saliendo. OPEN retorno: %d. (iteración %d) <<\n",
				   fd, i + 1);
			exit(1);
		} else if (buff == '1') {
			printf("Ejecutando... Iteración (%d)\n", i + 1);
		} else {
			printf("Ejecutando...\n");
		}
		sleep(i + 1);
		i++;
	}

	return 0;
}
