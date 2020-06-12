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
	sem_init(&semaforo, 0, 1);
	pthread_t productor, consumidor;

	pthread_create(&productor, NULL, *productor_Produce, NULL);
	pthread_create(&consumidor, NULL, *consumidor_Consume, NULL);

	pthread_join(productor, NULL);
	pthread_join(consumidor, NULL);

	return 0;
}

static void *productor_Produce(void *arg)
{
	while (producto < 1000) {

		if (producto < 8) {
			sem_wait(&semaforo);
			usleep(750000);
			producto++;
			printf("%s %d", " produciendo...\n", producto);
			sem_post(&semaforo);
		}
	}

	return 0;
}

static void *consumidor_Consume(void *arg)
{
	while (producto < 1000) {

		if (producto >= 4) {
			sem_wait(&semaforo);
			usleep(750000);
			producto--;
			printf("%s %d", " consumiendo...\n", producto);
			sem_post(&semaforo);
		}
	}

	return 0;
}
