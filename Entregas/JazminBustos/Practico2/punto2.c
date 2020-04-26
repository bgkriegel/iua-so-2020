#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int fd;
	char buf[1000];				// Tamaño del Buffer en Bytes
	ssize_t nr_bytes;

	fd = open("file", O_RDONLY);

	if (fd == -1) {
		printf("Error al abrir el archivo.\n");
	} else {
		nr_bytes = read(fd, buf, 200);	// Va a leer 200 caracteres
		close(fd);

		if (nr_bytes == 0) {
			printf("El archivo esta vacio!\n");
		} else {
			printf("%s", buf);
		}
	}

	return 0;
}
