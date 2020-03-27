/* Genere un archivo que contenga un listado extendido del contenido del directorio raiz (/).
   Escriba un programa que lea dicho archivo y muestre su contenido en pantalla.
   Para ello use las llamadas al sistema open(), close() y read().

   Tip: Para crear el archivo basta con hacer un 'ls -l' y redirigir su salida.
   Recuerde que cada proceso 'nace' con entrada estandar, salida estandar y error estandar.
   '<' redirige entrada std
   '>' redirige salida std, igual que '1>'
   '2>' redirige error std

  Tip: Para su programa debe:
  a) Abrir el archivo para lectura utilizando open()
  b) Recorrer el archivo haciendo read() y observando su valor de retorno,
     el mismo nos indica cuando hemos llegado al final del archivo.
  c) Cerrar el archivo

  Consejo: Siempre verifique valores de retorno de funciones (ver man page) ej.
  fd = open( "test.txt", O_RDONLY ); // verificar el valor de fd
  n = read( fd, buff, max ); // verificar n, su valor es importante */

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
		nr_bytes = read(fd, buf, 100);	// Va a leer 100 caracteres
		close(fd);

		if (nr_bytes == 0) {
			printf("Archivo vacio!\n");
		} else {
			printf("%s", buf);
		}
	}

	return 0;
}

// Para generar el archivo: $ sudo ls / -Ra > /home/mauro/file
