/*
	Ejemplo con semáforos POSIX
	Compilación:
	gcc -Wall -pthread -o semaforo P5-semaforos.c

	Uso:
	./semaforo uno
	./semaforo dos

	Explicación
	El primero que se lance crea un semaforo con nombre
	en /dev/shm/sem.semaforo_prueba, con valor inicial 0

	Cuando se ejecuta con argumento uno, se abre el semaforo
	y se hace un down()

	Cuando se ejecuta con argumento dos, se abre el semaforo
	y se hace un up()

	up() y down() se definen utilizando las funciones nativas,
	son solo un ejemplo

	Resultados posibles:
	Ejecutar uno y luego dos
	El primer proceso se bloquea, el segundo lo libera

	Ejecutar dos y uno
	El primer proceso incremente el sem y el segundo lo decrementa
	pero no se bloquea

	Ejecutar varios uno y luego varios dos
	Los uno se bloquean todos, hay que ejecutar tantos dos como unos
	para que todos se desbloqueen
*/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SEM_NAME "semaforo_prueba"

/* defino up() y down() */
void up( sem_t *t ) {
	sem_post( t );
}

void down( sem_t *t ) {
	sem_wait( t );
}

int main( int argc, char *argv[] ) {

	int pid = getpid();
	sem_t *s;

	if ( argc < 2 ) {
		printf("Faltan argumentos (uno|dos)\n");
		exit(1);
	}

	/* if arg = uno */
	if ( strcmp( argv[1], "uno" ) == 0 ) {
		printf("uno - %d\n", pid );

		/* abrimos(creamos) el semaforo valor inicial 0 */
		s = sem_open( SEM_NAME, O_CREAT, 0644, 0);
		if ( s == SEM_FAILED ) {
			perror("No puedo abrir semaforo");
			exit(2);
		}

		down( s );

		sem_close(s);
	}
	/* if arg = dos */
	else if ( strcmp( argv[1], "dos" ) == 0 ) {
		printf("dos - %d\n", pid );
		s = sem_open( SEM_NAME, O_CREAT, 0644, 0);
		if ( s == SEM_FAILED ) {
			perror("No puedo abrir semaforo");
			exit(2);
		}

		up( s );

		sem_close(s);
	}
	else {
		exit(3);
	}

	return 0;
}
