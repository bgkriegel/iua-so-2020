// Modern Operative Systems (4th Edition) by Tanenbaum and Bos.
// Chapter 2, Page 108

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

# define NUMBER_OF_THREADS 10

// This funtion prints the threads identidiers and then exits.
void *print_hello_world(void *tid)
{
	printf("Hello World. Greetings from thread %d\n", tid);
	pthread_exit(NULL);
}

// The main program creates 10 threads and then exits.
int main()
{
	pthread_t threads[NUMBER_OF_THREADS];
	int status, i;

	for(i = 0; i < NUMBER_OF_THREADS; i++)
	{
		printf("Main here. Creating thread %d\n", i);
		status = pthread_create(&threads[i], NULL, print_hello_world, (void *)i);

		if (status != 0)
		{
			printf("Oops. pthread_create returned error code %d\n", status);
			exit(-1);
		}
	}
	exit(NULL);
}

