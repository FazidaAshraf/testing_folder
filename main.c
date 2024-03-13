#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

//#define THREAD_NUM 8

sem_t semEmpty;
sem_t semFull;

pthread_mutex_t mutexBuffer;


int count = 0;

/*struct bufferData{
   int size;
   int numproducers;
   int numconsumers;
} sharedBuffer;
*/

void* producer(void* argds) {
   while (1) {
      // Produce
      int x = rand() % 10;
      sleep(1);
      // Add to the buffer
      sem_wait(&semEmpty);
      pthread_mutex_lock(&mutexBuffer);
      buffer[count] = x;
      count++;
      printf("number added to buffer: %d\n", x);
      pthread_mutex_unlock(&mutexBuffer);
      sem_post(&semFull);
   }
}

void* consumer(void* args) { //will this create new buffer array or what is this!?
   while (1) {
      int y;

      // Remove from the buffer
      sem_wait(&semFull);
      pthread_mutex_lock(&mutexBuffer);
      y = buffer[count - 1];
      count--;
      printf("number removed from the buffer: %d\n", y);
      pthread_mutex_unlock(&mutexBuffer);
      sem_post(&semEmpty);

      // Consume
      printf("Got %d\n", y);
      sleep(1);
   }
}
/*
TODO: function for additem to the buffer
  if bufffer full 

TODO: function for removeitem to the buffer
   if buffer empty
*/

int main(int argc, char* argv[]) {
   srand(time(NULL));
   if (argc != 4) {

      fprintf(stderr, "Usage: %s <buffer_size> <num_producers> <num_consumers>\n", argv[0]);
      return EXIT_FAILURE;
   }

   int buffersize = atoi(argv[1]);
   int numproducers = atoi(argv[2]);
   int numconsumers = atoi(argv[3]);

   sharedBuffer.size = buffersize;
   sharedBuffer.numproducers = numproducers;
   sharedBuffer.numconsumers = numconsumers;

   int buffer[sharedBuffer.size];

   pthread_t prod[numproducers];
   pthread_t cons[numconsumers];

   pthread_mutex_init(&mutexBuffer, NULL);
   sem_init(&semEmpty, 0, 10);
   sem_init(&semFull, 0, 0);

   int i,j;
   for (i = 0; i < numproducers; i++) {
      if (pthread_create(&prod[i], NULL, &producer, NULL) != 0) {
         perror("Failed to create producer thread\n");
      }
      printf("Created produce thread, P %d\n", i);
   }
   for (j=0; j<numconsumers; j++){
      if (pthread_create(&cons[j], NULL, &consumer, NULL)!= 0){

         perror("Failed to create consumer thread\n");
      }
      printf("Created consumer thread, C %d\n", j);
   }

   for (i = 0; i < numproducers; i++) {
      if (pthread_join(prod[i], NULL)!=0) {
         perror("Failed to join producer thread\n");
      }
   }
   for (j=0; i< numconsumers; j++){
      if (pthread_join(cons[i], NULL)!=0){
         perror("Failed to join consumer thread\n");
      }
   }
   printf("Successfully joined the produce and consumer threads\n");
   
   sem_destroy(&semEmpty);
   sem_destroy(&semFull);
   pthread_mutex_destroy(&mutexBuffer);
   return 0;
}