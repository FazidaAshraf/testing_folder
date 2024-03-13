#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_ITEMS 10
#ifndef PROD_CONS_MT_H
#define PROD_CONS_MT_H

struct bufferData{
   int size;
   int numproducers;
   int numconsumers;
};

extern pthread_mutex_t mutex;
extern pthread_cond_t full;
extern pthread_cond_t empty;
//extern struct bufferData;

void* producer(void* arg);
void* consumer(void* arg);
//void createThreads(int numproducers, int numconsumers);
//void joiningthread(int numproducers, int numconsumers);