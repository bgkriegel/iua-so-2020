/**************************************************************\
 Autor: Leonel Pacha
 Practico: 5
 Objetivo: Problema del productor/consumidor resuelto con semaforos
 Fecha: 05/06/2020
\**************************************************************/

/*Utilice de referencia un ejemplo subido por el profe que implementa 
la solución mediante el uso de hilos

Para compilar:
gcc -Wall -o Practico.c Practico -pedantic -pthread
*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

static void * productor_Produce (void* arg);
static void * consumidor_Consume (void* arg);

static int producto = 0;		//inicializo los productos
sem_t semaforo;  	//creo el semaforo

int main () {

	sem_init (&semaforo, 0, 1); 
	
	/*Inicializo el semaforo con la función sem_init(sem_t *sem, int pshared, unsigned value) que está referido con sem. 
	El valor de inicializado es value. La variable que pide en pshared es un valor diferente de cero, si lo es, entonces el semáforo es
    compartido entre procesos*/

	pthread_t consumidor, productor; //creo los hilos

	pthread_create (&consumidor, NULL,*consumidor_Consume, NULL ); //inicializo hilo de consumidor
	pthread_create (&productor, NULL,*productor_Produce, NULL );   //inicializo hilo de productor
	
	/*Inicializo los hilos con pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg) donde 
	*thread referencia al hilo, luego el argumento attr apunta a una estructura pthread_attr_t cuyo contenidose utilizan en el momento de creación 
	de subprocesos para determinar los atributos para el nuevo hilo; si attr es NULL, entonces el hilo se crea con atributos por defecto.
	Los otros dos argumentos son alguna funcion que se ejecutará al crearse el hilo y su respectivo argumento de entrada (en este caso null)
	Una llamada exitosa a pthread_create() almacena la ID del nuevo hilo en el buffer señalado por thread*/
	
	pthread_join(consumidor, NULL);
	pthread_join(productor, NULL);
	
	/*La función pthread_join(pthread_t thread, void **retval) espera el hilo especificado por thread para terminar. 
	Si ese hilo ya ha terminado, entonces regresa inmediatamente.*/
	
	return 0;
	
}



static void * productor_Produce (void* arg) {		//Función del productor

	while (producto < 1000) {
			
		if (producto < 8) {  // Si hay menos de 8 productos, empieza a producir
	
			sem_wait (&semaforo); 
			
			/*La función sem_wait() disminuye (bloquea) el semáforo señalado. Si el valor del semáforo es mayor que cero, 
			entonces la disminución continúa, y la función regresa, inmediatamente. Si el semáforo actualmente tiene el valor cero, 
			luego la llamada se bloquea hasta que se hace posible realizar la disminución (es decir, el valor del semáforo se eleva 
			por encima de cero), o un controlador de señal interrumpe la llamada.
			En este uso, se reserva el turno para modificar los productos*/
			
			usleep(750000); //espero 0.75 segundos
			
			producto++;    //produzco un producto
			
			printf("Produciendo productos, llevo hechos: %d\n", producto);

			sem_post(&semaforo); 
			
			/*La función sem_post() incrementa (desbloquea) el semáforo señalado. Si el valor del semáforo en consecuencia 
			se vuelve mayor que cero, entonces se despertará otro proceso o subproceso bloqueado.
			En este uso, se libera la funcion devolviendo los productos*/
		
			}
	}

}


static void * consumidor_Consume (void* arg) {		//Función del consumidor

	while (producto < 1000)	{
		
		if (producto > 4) {  // Si hay 5 o más productos, consume productos
			
			sem_wait(&semaforo); //Reserva su turno para modificar los productos
			
			usleep(750000); //espero 0.75 de segundo
			
			producto --;    //consumo productos
			
			printf("Consumiendo productos, quedan: %d\n", producto);

			sem_post(&semaforo); //Libera los productos
		}

	}

}
