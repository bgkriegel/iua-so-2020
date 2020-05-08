/* Problema del productor/consumidor: Se le pide que resuelva el problema clasico del productor/consumidor, utilizando como base el código de la solución utilizando semáforos presentado en el libro.
   Dicho código, que no compila y muy incompleto, es el siguiente:

	// BEGIN código del libro
	#define N 100 // number of slots in the buffer
	typedef int semaphore;	// semaphores are a special kind of int
	semaphore mutex = 1;	// controls access to critical region
	semaphore empty = N;	// counts empty buffer slots
	semaphore full = 0;	// counts full buffer slots

	void producer(void)
	{
		int item;
		while (TRUE) { 			// TRUE is the constant 1
			item = produce item( );	// generate something to put in buffer
			down(&empty); 		// decrement empty count
			down(&mutex); 		// enter critical region
			inser t item(item); 	// put new item in buffer
			up(&mutex); 		// leave critical region
			up(&full); 		// increment count of full slots
		}
	}

	void consumer(void)
	{
		int item;
		while (TRUE) { 			// infinite loop
			down(&full); 		// decrement full count
			down(&mutex); 		// enter critical region
			item = remove item( ); 	// take item from buffer
			up(&mutex); 		// leave critical region
			up(&empty); 		// increment count of empty slots
			consume item(item); 	// do something with the item
		}
	}
	// END código del libro

  Claramente esto no funciona de forma directa, los semáforos no son enteros, pero nos muestra un poco la idea.
  Recordar que tan to productor como consumidor deben ser procesos o hilos independientes independientes.

  Hay que investigar:
  1) Semáforos: se utilizarán semáforos POSIX
  2) Tipos de semáforos: con/sin nombre, uso similar a tuberías
  3) Como se declara y accede a un semáforo
  4) Como se hacen las operaciones equivalentes a up() y down()

  Par esto pueden leer las páginas de manual de sem_overview, sem_wait y sem_post.
  También https://users.cs.cf.ac.uk/Dave.Marshall/C/node26.html#SECTION002640000000000000000

  Un esquema de la solución podría ser:
  1) Utilizamos semáforos sin nombre (procesos relacionados)
  2) Un proceso padre que crea e incializa los semáforos necesarios
  3) Se crean dos procesos hijos para productor y consumidor
  4) los hijos utilizan una espera aleatoria cuando producen/consumen
  5) los hijos muestran su actividad
  6) luego de un nro finito de items se termina

  La variante que utiliza semáforos con nombre es parecida pero para procesos independientes, uno de ellos crea e inicializa los
  semáforos, luego 'espera' a que el otro esté en línea para comenzar ambos el ciclo. */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

static void *productor_Produce(void *arg);
static void *consumidor_Consume(void *arg);
static int producto = 0;
sem_t semaforo;

int main(void)
{
	sem_init(&semaforo, 0, 1);	 // Creando el Semaforo.
	pthread_t productor, consumidor; // Inicializando los hilos.

	pthread_create(&productor, NULL, *productor_Produce, NULL);	// Creo el hilo de Productor.
	pthread_create(&consumidor, NULL, *consumidor_Consume, NULL);	// Creo el hilo de Consumidor.

	pthread_join(productor, NULL);
	pthread_join(consumidor, NULL);

	return 0;
}

static void *productor_Produce(void *arg)
{
	while (producto < 1000) {
		// Produce si quedan menos de 8 productos.
		if (producto < 8) {
			sem_wait(&semaforo);	// Reserva su turno para modificar los productos.
			usleep(750000);		// Espera 0.75 segundos.
			producto++;		// Produce.
			printf("%s %d", " produciendo...\n", producto);
			sem_post(&semaforo);	// Libera los productos.
		}
	}

	return 0;
}

static void *consumidor_Consume(void *arg)
{
	while (producto < 1000) {
		// Consume si hay 5 o mas productos.
		if (producto >= 4) {
			sem_wait(&semaforo);	// Reserva su turno para modificar los productos.
			usleep(750000);		// Espera 0.75 segundos.
			producto--;		// Consume.
			printf("%s %d", " consumiendo...\n", producto);
			sem_post(&semaforo);	// Libera los productos.
		}
	}

	return 0;
}

// Para compilar: gcc -Wall -o semaforo semaforo.c -pedantic -pthread
