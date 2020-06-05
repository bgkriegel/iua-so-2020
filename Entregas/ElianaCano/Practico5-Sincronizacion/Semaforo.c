#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>


// Semaforos usando Hilos

static void * producir(void* arg); //prototipos de función
static void * consumir(void* arg);

static int producto = 0; //para que pueda accederce desde cualquier parte del código
sem_t sem;  //instancio el semáforo

int main(void)
{

//*******Semáforo*********

sem_init(&sem,0,1); //creo el semaforo


//sem_init(dirección del semáforo (sem),el semáforo es compartido con todos los hilos de este proceso,valor de inicializacion);

//Explicación del valor del semáforo:

/*Imaginemos que el semáforo controla un fichero y que inicialmente tiene el valor 1 (está "verde").
 Cuando un proceso quiere acceder al fichero, primero debe decrementar el semáforo. El contador queda
a 0 y como no es negativo, deja que el proceso siga su ejecución y, por tanto, acceda al fichero.

Ahora un segundo proceso lo intenta y para ello también decrementa el contador. Esta vez el contador
se pone a -1 y como es negativo, el semáforo se encarga de que el proceso quede "bloqueado" y
"dormido" en una cola de espera. Este segundo proceso no continuará por tanto su ejecución y no
accederá al fichero. */

//***********Hilos***********

	pthread_t consumidor, productor; //Instancio los hilos consumidor y productor.

	pthread_create(&consumidor, NULL,*consumir, NULL ); // Crear hilo
	pthread_create(&productor, NULL,*producir, NULL );   // Crear hilo
    
	//pthread_create(dirección del hilo, atributos,función que se ejecuta cuando se crea el hilo, argumento de entrada de la función;

	pthread_join(consumidor, NULL);// Para que el hilo espere a que termine de ejecutarse el otro.
	pthread_join(productor, NULL);//

	return 0;
}

//***********Funciones**********

static void * producir(void* arg)
{

	while(producto < 1000) //el máximo es 500
	{
		
	if(producto < 8) // Si quedan menos de 8 productos produce
		{
		sem_wait(&sem); //La función sem_wait () bloqueará el semáforo al que hace referencia (sem) mediante la realización de una
        //operación de bloqueo. Si el valor del semáforo es actualmente cero (es decir, que cuando lo decremente quedará en -1,
        //que es negativo), entonces el hilo de llamada no regresará de la llamada a sem_wait () hasta que bloquee el semáforo o
        //la llamada se interrumpa por una señal.

//Al regresar con éxito, el estado del semáforo se bloqueará y permanecerá bloqueado hasta que la
//función sem_post () se ejecute y regrese con éxito.

		usleep(750000); //espera
		producto ++;    //producir
		printf("Produciendo... Cantidad de productos: %d \n", producto);
		sem_post(&sem); //Libera los productos
		}

	}

}


static void * consumir(void* arg)
{

	while(producto < 1000)
	{
		
	if(producto > 4)   //Si hay 5 o mas productos consume
		{
		sem_wait(&sem); 
		usleep(750000);
		producto --;    //consumir
		printf("Consumiendo... cantidad de productos: %d \n", producto);
		sem_post(&sem); //Libera los productos
		}

	}

}

//Preguntar por qué PAblo compila así:
// gcc EjercicioSemaforo.c -o EjercicioSemaforo -Wall -pedantic -pthread

//si el profe compila así: gcc -Wall -pthread -o semaforo P5-semaforos.c





