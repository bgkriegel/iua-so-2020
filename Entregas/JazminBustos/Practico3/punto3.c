#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BYTES 1

int main()
{

	int fd, i = 1;
	char buff;

	while (i > 0) {




		fd = open("txt.txt", O_RDONLY | O_CREAT);

		if (fd == -1) {
			printf("ERROR, NO SE PUDO ABRIR \n");
			exit(1);
		} else {
			read(fd, &buff, MAX_BYTES);
			if (buff == '1') {
				printf("ESTA CORRIENDO\n");
				sleep(1);
			} else {
				if (buff == '0') {
					printf(" Numero de interacion:%d\n", i);

					exit(1);
				} else {
					printf(" 1 para continuar o 0 para cerrar\n");

					sleep(1);
				}



			}

		}

		i++;


	}
	while (1) {

		fd = open("txt.txt", O_RDWR | O_CREAT, 0644);

		sleep(1);

		read(fd, &buff, 0);


		printf("sE MODIFICO, CERRANDO.\n");

		escritor = write(fd, "0", MAX_BYTES);

		if (escritor > 0) {


			printf("SE MODIFICO.\n");

			printf("SE VA A CERRAR.\n");

			exit(1);

		} else {
			printf("NO SE MODIFICO.\n");
		}

	}

	close(fd);

	return 0;

}
