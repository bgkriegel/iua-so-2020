#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>


// Semaforos usando Hilos

static void * productor_Produce(void* arg);//Prototipados
static void * consumidor_Consume(void* arg);

static int producto = 0;
sem_t semaforo;  //Inicializo el semaforo

int main(void)
{

/////////////////////////Semaforo////////////////////////////////////////////////////////7

sem_init(&semaforo,0,1); //creo el semaforo


//sem_init(referencia al semaforo,el semaforo es compartido entre procesos ?,valor de inicializacion);

////////////////////////Hilos///////////////////////////////////////////////////////////////////////


	pthread_t consumidor, productor; //Inicializo los hilos

	pthread_create(&consumidor, NULL,*consumidor_Consume, NULL ); // Creo hilo de consumidor
	pthread_create(&productor, NULL,*productor_Produce, NULL );   // Creo hilo de productor
	//pthread_create(referencia al hilo, atributos,funcion que se ejecutara al crearse el hilo, argumento de entrada de la funcion );



	pthread_join(consumidor, NULL);// Los hilos esperan a que termine el otro
	pthread_join(productor, NULL);//

///////////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}

static void * productor_Produce(void* arg)
{

	while(producto < 1000)
	{
		
	if(producto < 8) // Si quedan menos de 8 productos produce
		{
		sem_wait(&semaforo); //Reserva su turno para modificar los productos
		usleep(750000); //espero 3/4 de segundo
		producto ++;
		printf("%s %d","Produciendo... Productos:", producto);
		printf("\n");
		sem_post(&semaforo); //Libera los productos
		}

	}

}


static void * consumidor_Consume(void* arg)
{

	while(producto < 1000)
	{
		
	if(producto >= 4)   //Si hay 5 o mas productos consume
		{
		sem_wait(&semaforo); //Reserva su turno para modificar los productos
		usleep(750000); //espero 3/4 de segundo
		producto --;
		printf("%s %d","Consumiendo... Productos:", producto);
		printf("\n");
		sem_post(&semaforo); //Libera los productos
		}

	}

}

//Para compilar
// gcc EjercicioSemaforo.c -o EjercicioSemaforo -Wall -pedantic -pthread





