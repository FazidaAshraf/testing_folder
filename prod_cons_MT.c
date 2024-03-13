#include <stdio.h>
#include <stdlib.h>
#include "prod_cons_MT.h"

struct bufferData{
   int size;
   int numproducers;
   int numconsumers;
};

int size = bufferData.size;
int buffer[size];

int in = 0;
int out = 0;
int produced_count = 0;
int consumed_count = 0;
int BUFFER_SIZE = sizeof(buffer);
int i,j;

void* producer(void* arg) {

    while (produced_count < MAX_ITEMS) {
        pthread_mutex_lock(&mutex);
        while (((in + 1) % BUFFER_SIZE) == out) {
            pthread_cond_wait(&empty, &mutex);
        }
        int x = rand() % 10 +1;
        buffer[in] = x;
        printf("P%d", in);
        printf(": Writing %d ", x, " to position %d", in);
        //printf("Produced: %d\n", x);
        //printf("the index is: %d\n", in);
        in = (in + 1) % BUFFER_SIZE;
        produced_count++;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    while (consumed_count < MAX_ITEMS) {
        pthread_mutex_lock(&mutex);
        while (in == out) {
            pthread_cond_wait(&full, &mutex);
        }
        int item = buffer[out];
        printf("Consumed: %d\n", item);
        printf("consumed index is at: %d\n", out);
        out = (out + 1) % BUFFER_SIZE;
        consumed_count++;
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}
/*void createThreads(int numproducers, int numconsumers){
    for (i = 0; i < numproducers; i++) {
        if (pthread_create(&prod[i], NULL, &producer, NULL) != 0) {
            perror("Failed to create producer thread\n");
    }
    printf("Main: started producer %d\n", i);

    }

    for (j=0; j<numconsumers; j++){
        if (pthread_create(&cons[j], NULL, &consumer, NULL)!= 0){
            perror("Failed to create consumer thread\n");
        }
        
    printf("Main: started consumer %d\n", i);

   }
}

void joiningthread(int numproducers, int numconsumers){
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
}
*/
/*
TODO: add_item()
    if full:
        "Blocked due to full buffer!"


TODO: remove_item()
    if empty:
        "Blocked due to empty buffer!"
*/
