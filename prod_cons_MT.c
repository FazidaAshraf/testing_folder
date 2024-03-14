#include <stdio.h>
#include <stdlib.h>
#include "prod_cons_MT.h"

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
        printf(": Writing %d to position %d\n", x, in);
        //if full, print message!
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
        //if empty, print message
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
