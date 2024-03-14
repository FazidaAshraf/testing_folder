#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define BUFFER_SIZE 6
#define MAX_ITEMS 6

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int produced_count = 0;
int consumed_count = 0;
int i,j;

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;

void* producer(void* arg) {
    int array[6];
    for (produced_count = 0; produced_count <MAX_ITEMS; produced_count++){
        int x = rand() % 10;
        array[produced_count] = x;
        printf("P%d: Producing 6 values\n", i);
        pthread_mutex_lock(&mutex);
        while (((in + 1) % BUFFER_SIZE) == out) {
            pthread_cond_wait(&empty, &mutex);
        }
    }
    /*while (produced_count < MAX_ITEMS) {
        int x = rand() % 10;
        array[produced_count] = x;
        produced_count++;
    */
        for(int a; a < 6; a++){
            buffer[a] = array[a];
            printf(" Writing %d to position %d", buffer[a], array[a]);
        }
        if (sizeof(buffer) == BUFFER_SIZE){
            printf("Blocked due to full buffer, P:%d\n", i);
        }
        

        //buffer[in] = x;

        //printf("Produced: %d\n", x);
        //printf("the index is: %d\n", in);

        in = (in + 1) % BUFFER_SIZE;
        
        printf("in value is: %d\n", in);
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    
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

int main(int argc, char* argv[]) {
    srand(time(NULL));
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <buffer_size> <num_producers> <num_consumers>\n", argv[0]);
        return EXIT_FAILURE;
    }

   //int buffersize = atoi(argv[1]);
   int numproducers = atoi(argv[2]);
   int numconsumers = atoi(argv[3]);

    pthread_t prod[numproducers];
    pthread_t cons[numconsumers];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
 
    for (i = 0; i < numproducers; i++) {
    if (pthread_create(&prod[i], NULL, &producer, NULL) == 0) {
        printf("Main: started producer %d\n", i);
    }
        printf("Failed to create producer thread%d\n", i);
        &producer;
    }
    for (j=0; j<numconsumers; j++){
        if (pthread_create(&cons[j], NULL, &consumer, NULL)!= 0){
            perror("Failed to create consumer thread\n");
        }
        printf("Created consumer thread, C %d\n", j);
        &consumer;
    }
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

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

    return 0;

}