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

    //createThreads(numproducers, numconsumers);
    //joiningThreads(numproducers, numconsumers);

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