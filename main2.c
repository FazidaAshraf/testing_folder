#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#define BUFFER_SIZE 10
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int produced_count = 0;
int consumed_count = 0;
int i,j;


pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;

/*struct for buffer!
typedef struct {
    size_t head;
    size_t tail;
    size_t size;
    void** data;
} queue_t;

void* buffer_read(buffer_t *buffer) {
    if (buffer->tail == buffer->head) {
        return NULL;
    }
    void* handle = buffer->data[buffer->tail];
    buffer->data[buffer->tail] = NULL;
    buffer->tail = (buffer->tail + 1) % buffer->size;
    return handle;
}

int buffer_write(buffer_t *buffer, void* handle) {
    if (((buffer->head + 1) % buffer->size) == buffer->tail) {
        return -1;
    }
    buffer->data[buffer->head] = handle;
    buffer->head = (buffer->head + 1) % buffer->size;
    return 0;
}

void bufferqueue(){
    buffer_t example = {0, 0, BUFFER_SIZE, malloc(sizeof(void*) * BUFFER_SIZE)};
  
    // Write until queue is full
    for (int i=0; i<BUFFER_SIZE; i++) {
        int res = queue_write(&example, (void*)(i+1));
        assert((i == BUFFER_SIZE - 1) ? res == -1: res == 0);
    }
    // Read until queue is empty
    for (int i=0; i<BUFFER_SIZE; i++) {
        void* handle = queue_read(&example);
        assert((i == BUFFER_SIZE - 1) ? handle == NULL: handle == (i+1));
    }
}

*/
void* producer(void* arg) {
    printf("Main: started producer %d\n", i);
    for (produced_count = 0; produced_count <MAX_ITEMS; produced_count++){
        int x = rand() % 10;
        array[produced_count] = x;
        printf("P%d: Producing 6 values\n", i);
    }

    while (produced_count < MAX_ITEMS) {
        pthread_mutex_lock(&mutex);
        while (((in + 1) % BUFFER_SIZE) == out) {
            pthread_cond_wait(&empty, &mutex);
        }
        //int x = rand() % 10;
        buffer[in] = x;
        printf("number: %d produced in producer: %d\n", x, i);
        printf("the index is: %d\n", in);
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
     
    for (i = 0; i < numproducers; i++) {
        //printf("value of i is: %d\n",i);
        if (pthread_create(&prod[i], NULL, &producer, NULL) != 0) {
            perror("Failed to create producer thread\n");
        }
    }
    for (j=0; j<numconsumers; j++){
        if (pthread_create(&cons[j], NULL, &consumer, NULL)!= 0){
            perror("Failed to create consumer thread\n");
        }
        printf("Created consumer thread, C %d\n", j);
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