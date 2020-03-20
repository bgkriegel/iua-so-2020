// Modern Operative Systems (4th Edition) by Tanenbaum and Bos.
// Chapter 2, Page 108
// Fix by Bernardo Krieger

 #include <stdio.h>
 #include <stdlib.h>
 #include <pthread.h>

 # define NUMBER_OF_THREADS 10

 // This function prints the threads identifiers and then exits.
 void *print_hello_world(void *tid)
 {
         printf("Hello World. Greetings from thread %p\n", tid);
         pthread_exit(NULL);
 }

 // The main program creates 10 threads and then exits.
 int main()
 {
         pthread_t threads[NUMBER_OF_THREADS];
         int status,i;
         pthread_t p;

         for(i = 0; i < NUMBER_OF_THREADS; i++)
         {
                 printf("Main here. Creating thread %d\n", i);
                 p = i;
                 status = pthread_create(&threads[i], NULL, print_hello_world, (void*) p);

                 if (status != 0)
                 {
                         printf("Oops. pthread_create returned error code %d\n", status);
                         exit(-1);
                 }
         }

         return 0;
 }

// To compile: gcc -Wall -pthread -o pthreads pthreads_2.c
// To execute: ./pthreads
