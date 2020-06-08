//Sistemas Operativos - Sinronización (1)
//---------------------------------------
//
//Objetivo: Problema del productor/consumidor
//
//1) Utilizamos semáforos sin nombre (procesos relacionados)
//2) Un proceso padre que crea e incializa los semáforos necesarios
//3) Se crean dos procesos hijos para productor y consumidor
//4) los hijos utilizan una espera aleatoria cuando producen/consumen
//5) los hijos muestran su actividad
//6) luego de un nro finito de items se termina

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

static void *producer_prod(void *arg);

static void *consumer_cons(void *arg);

#define LOOP 9999 /* number of times the thread will work */
static int item = 0; /* product buffer */
sem_t sem; /* our semaphore */

int main() {
    sem_init(&sem, 0,
             1); /* initializing semaphore (sem adress, 0 between threads or 1 between processes, initial value)  */
    pthread_t producer, consumer; /* threads for consumer and producer */
    pthread_create(producer, NULL, producer_prod, NULL); /* creating... */
    pthread_create(consumer, NULL, consumer_cons, NULL); /* ...threads */

    pthread_join(consumer, NULL); /* waiting for threads to stop */
    pthread_join(producer, NULL); /* idem */
    return 0;
}

/* thread functions */

static void *producer_prod(void *arg) {
    int item;
    for (int i = 0; i < LOOP; i++) {
        if (item < 100) { /* if there are 99 or less products in stock */
            sem_wait(&sem); /* decreases semaphore value, this way we block the other thread */
            usleep(1000000); /* wait 1 second */
            item++; /* add a product to stock */
            printf("producing item number: %d.\n", item); /* showing activity */
            sem_post(&sem); /* increases semaphore value to unlock it */
        }
    }
}

static void *consumer_cons(void *arg) {
    for (int i = 0; i < LOOP; i++) {
        if (item > 1) {
            sem_wait(&sem);
            usleep(1000000);
            item--;
            printf("consuming item number: %d.\n", item);
            sem_post(&sem);
        }
    }
}
