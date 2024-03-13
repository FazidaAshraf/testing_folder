#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "prod_cons_MT.h"

#define MAX_ITEMS 10

int main(int argc, char* argv[]){
    srand(time(NULL));
   if (argc != 4) {

      fprintf(stderr, "Usage: %s <buffer_size> <num_producers> <num_consumers>\n", argv[0]);
      return EXIT_FAILURE;
   }

    int buffersize = atoi(argv[1]);
    int numproducers = atoi(argv[2]);
    int numconsumers = atoi(argv[3]);

    struct bufferData sharedBuffer;
    sharedBuffer.size = buffersize;

    printf("The value of buffersize = %d\n", sharedBuffer.size);

    createThreads(numproducers, numconsumers);
    joiningThreads(numproducers, numconsumers);
    

    //pthread_t producerThread, consumerThread;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    //pthread_create(&producerThread, NULL, producer, NULL);
    //pthread_create(&consumerThread, NULL, consumer, NULL);
    //pthread_join(producerThread, NULL);
    //pthread_join(consumerThread, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
    return 0;

}