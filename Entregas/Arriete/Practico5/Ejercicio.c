#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>


sem_t semaforo,lleno,vacio;
void* producirProductor(void *args);
void* consumirConsumidor(void *args);
int producto = 40;
int numero = 4;


int main()
{
	pthread_t productor, consumidor;

	sem_init(&semaforo, 0, 1);
	sem_init(&vacio, 0, numero);
	sem_init(&lleno, 0, 0);

	pthread_create(&productor, NULL, *producirProductor, NULL);
	pthread_create(&consumidor, NULL, *consumirConsumidor, NULL);

	pthread_join(productor, NULL);
	pthread_join(productor, NULL);

	sem_destroy(&semaforo);
	sem_destroy(&vacio);
	sem_destroy(&lleno);

	printf("El programa ha finalizado\n");

	return 0;
}

void* producirProductor(void* args) {
  for (int i = 0; i < producto; i++) {

    sem_wait(&vacio);
    sem_wait(&semaforo);
    usleep(1000000000);
	printf("Se esta produciendo:%d\n",(i+1));
	sem_post(&semaforo);
 	sem_post(&lleno);
 
  }

  return NULL;
}


void* consumirConsumidor(void* args) {
  for (int i = 0; i < producto; i++) {
  	
		sem_wait(&lleno);
		sem_wait(&semaforo);
		usleep(1000000000);
    	printf("Se esta consumiendo: %d\n",(i+1));
		sem_post(&semaforo);
	    sem_post(&vacio);

  }

  return NULL;
}