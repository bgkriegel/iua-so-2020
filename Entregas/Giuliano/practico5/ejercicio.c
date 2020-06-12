#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

static void * productor_Produce (void* arg);
static void * consumidor_Consume (void* arg);
static int producto = 0;
sem_t semaforo; 

int main () {

	sem_init (&semaforo, 0, 1); 
	pthread_t consumidor, productor;

	pthread_create (&consumidor, NULL,*consumidor_Consume, NULL );
	pthread_create (&productor, NULL,*productor_Produce, NULL );

	pthread_join(consumidor, NULL);
	pthread_join(productor, NULL);

	return 0;
}

static void * productor_Produce (void* arg) {

	while (producto < 1000) {
		if (producto < 8) {
			sem_wait (&semaforo); 
			usleep(750000);
			producto++;
			printf("Produciendo productos, llevo hechos: %d\n", producto);
			sem_post(&semaforo); 
			}
	}
}

static void * consumidor_Consume (void* arg) {

	while (producto < 1000)	{
		if (producto > 4) {
			sem_wait(&semaforo);
			usleep(750000);
			producto --; 
			printf("Consumiendo productos, quedan: %d\n", producto);
			sem_post(&semaforo);
		}
	}
}
