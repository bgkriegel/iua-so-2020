/**************************************************************\
 Autor: Ivan Guerra
 Practico: 5
 Objetivo: Problema del productor/consumidor.
  - Resolver el problema clasico del productor/consumidor, utilizando como base el 
    código de la solución utilizando semáforos presentado en el libro.
  - Se debe investigar:
      1) Semáforos: se utilizarán semáforos POSIX
      2) Tipos de semáforos: con/sin nombre, uso similar a tuberías
      3) Como se declara y accede a un semáforo
      4) Como se hacen las operaciones equivalentes a up() y down()
  - Un esquema de la solución puede ser:
      1) Utilizar semáforos sin nombre (procesos relacionados)
      2) Un proceso padre crea e inicializa los semáforos necesarios
      3) Se crean dos procesos hijos para productor y consumidor
      4) Los hijos utilizan una espera aleatoria cuando producen/consumen
      5) Los hijos muestran su actividad
      6) Luego de un nro finito de items se termina
  - La variante que utiliza semáforos con nombre es parecida pero para procesos independientes. 
    Uno de ellos crea e inicializa los semáforos, luego 'espera' a que el otro esté en línea 
    para comenzar ambos el ciclo.
 Fecha: 13/05/2020
\**************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// Declaracion de semaforos
sem_t mutex, emptySlots, fullSlots;

// Tamaño del buffer
#define SLOTS 5

// Cantidad de items a generar
#define ITEMS 30

// Declaracion de funcionar a utilizar por los hilos prod y consum.
void* producir(void* args);
void* consumir(void* args);

int main () {
	// Declaracion de hilos
  pthread_t hilo_prod, hilo_cons;

  printf("PROBLEMA DEL PROD/CONSUM UTILIZANDO SEMAFOROS EN C.\n");
  printf("--------------------------------------------------.\n\n");

	// Inicializacion de semaforos

	// Semaforo mutex para alternancia estricta. Inicializo a valor 1
  sem_init(&mutex, 0, 1);
	// Semaforo emptySlots que representa los espacios vacios del buffer acotado. Inicializo al valor tamaño del buffer (SLOTS).
  sem_init(&emptySlots, 0, SLOTS);
	// Semaforo fullSlots que representa los espacios llenos del buffer acotado. Inicializo al valor 0 (cero).
  sem_init(&fullSlots, 0, 0);
  
	// Creacion de hilos

	// Hilo del productor
  pthread_create(&hilo_prod, NULL, *producir, NULL);
	// Hilo del consumidor
  pthread_create(&hilo_cons, NULL, *consumir, NULL);

	// Espero que terminen de ejecutarse los hilos antes de terminar la ejecucion del programa.
  pthread_join(hilo_prod, NULL);
  pthread_join(hilo_prod, NULL);

	// Destruyo los semaforos
  sem_destroy(&mutex);
  sem_destroy(&emptySlots);
  sem_destroy(&fullSlots);

  printf("\n----------------\n");
  printf("PROGRAMA TERMINADO\n");

	// Termino el programa
  return 0;
}

void* producir(void* args) {
  for (int i = 0; i < ITEMS; i++) {
	
		// Intento decrementar el semaforo de espacios vacios en el buffer. Si el valor del semaforo
		// es menor a 0 (cero), se bloquea el hilo hasta que el consumidor retire un elemento del 
		// buffer y lo despierte.
    sem_wait(&emptySlots);

		// Decremento el valor del semaforo mutex para indicar que voy a entrar en la region critica.
    sem_wait(&mutex);

		// Espero 0.25 seg. antes de producir
		usleep(250000);

    // PRODUCIR
    printf("Producido: %d\n", (i+1));

		// Incremento el valor del semaforo mutex para indicar que voy a salir de la region critica.
    sem_post(&mutex);
 
 		// Incremento el valor del semaforo fullSlots para indicar que hay un nuevo espacio lleno 
		// en el buffer.
    sem_post(&fullSlots);

  }

  return NULL;
}


void* consumir(void* args) {
  for (int i = 0; i < ITEMS; i++) {

		// Intento decrementar el semaforo de espacios llenos en el buffer. Si el valor del semaforo
		// es menor a 0 (cero), se bloquea el hilo hasta que el productor coloque un elemento en el  
		// buffer y lo despierte.
    sem_wait(&fullSlots);

		// Decremento el valor del semaforo mutex para indicar que voy a entrar en la region critica.
    sem_wait(&mutex);

		// Espero 0.45 seg. antes de consumir
		usleep(450000);

    // CONSUMIR
    printf("Consumido: %d\n", (i+1));

		// Incremento el valor del semaforo mutex para indicar que voy a salir de la region critica.
    sem_post(&mutex);

 		// Incremento el valor del semaforo emptySlots para indicar que hay un nuevo espacio vacio 
		// en el buffer.
    sem_post(&emptySlots);
  
	}

  return NULL;
}

// Para compilar: gcc -Wall -pedantic -pthread -o prod_consum_semaforos prod_consum_semaforos.c
// Para ejecutar: ./prod_consum_semaforos