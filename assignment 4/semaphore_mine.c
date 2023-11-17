#include<stdlib.h>
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 2


int buffer[BUFFER_SIZE]; // critical section / array size
int in = 0; // denotes at which position element supposed to be added
int out = 0; // denotes at which position element is supposed to be removed (while removing equate it to 0)
sem_t empty; // initialise empty semaphore 
sem_t full; // initialise semaphore for full
sem_t mutex; // initialise semaphore for mutex

void *producer(void *arg) {
    int index;
    while(1){
        index = (rand() % BUFFER_SIZE) + 1; // generate random index for insertion 
        sem_wait(&empty); // wait empty 
        sem_wait(&mutex); // wait mutex 
        buffer[in] = index;
        in = (in + 1) % BUFFER_SIZE;
        printf("Producer no : %d, produced %d \n", *((int *)arg), index);
        sem_post(&mutex);
        sem_post(&full);
        sleep(2);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    while(1){
        sem_wait(&full);
        sem_wait(&mutex);
        int consum = buffer[out];
        buffer[out] = 0;
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumer no : %d, consumed %d \n", *((int *)arg), consum);
        sem_post(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    for(int i=0; i<BUFFER_SIZE; i++){
        buffer[i] = 0;
    }
    pthread_t producers[NUM_PRODUCERS]; // create an array of threads for producers 
    pthread_t consumers[NUM_CONSUMERS]; // for consumers
    int producer_id[NUM_PRODUCERS]; // producer ids
    int consumer_id[NUM_CONSUMERS]; // consumer ids

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    //printf("Hello World\n");
    
    for(int i=0; i<NUM_PRODUCERS; i++){
        producer_id[i] = (i+1);
        pthread_create(&producers[i], NULL, producer, &producer_id[i]);
    }

    for(int i=0; i<NUM_CONSUMERS; i++){
        consumer_id[i] = (i+1);
        pthread_create(&consumers[i], NULL, consumer, &consumer_id[i]);
    }

    while(1) {
        // for whatever purpose ?? 
    }
    
    sem_destroy(&empty);
    sem_destroy(&mutex);
    sem_destroy(&full);
}