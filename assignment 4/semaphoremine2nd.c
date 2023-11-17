#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define BUFFER_SIZE 5
#define NOFPRODUCERS 3
#define NOFCONSUMERS 2

sem_t empty;
sem_t full;
sem_t mutex;
int in = 0;
int out = 0;
int buffer[BUFFER_SIZE];

void *producer(void * arg) {
    int index;
    while(1) {
        index = rand() % 10;
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = index;
        in = (in + 1) % BUFFER_SIZE;
        printf("Producer %d produced element %d\n", (*(int *)arg), index);
        sleep(5);
        sem_post(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consumer(void * arg) {
    while(1) {
        sem_wait(&full);
        sem_wait(&mutex);
        int index = buffer[out];
        buffer[out] = 0;
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumer %d consumed element %d\n", (*(int *)arg), index);
        sleep(3);
        sem_post(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}


int main() {
    printf("START\n");
    //printf("Enter the number of producers \n");
    //scanf("%d", &nofproducers);
    //printf("Enter the number of consumers \n");
    //scanf("%d", &nofconsumers);
    pthread_t producers[NOFPRODUCERS];
    pthread_t consumers[NOFCONSUMERS];
    int producers_ind[NOFPRODUCERS];
    int consumer_ind[NOFCONSUMERS];
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    for(int i=0; i<BUFFER_SIZE; i++) {
        buffer[i] = 0;
    }
    for(int i=0; i<NOFPRODUCERS; i++) {
        producers_ind[i] = (i + 1);
        pthread_create(&producers[i], NULL, producer, &producers_ind[i]);
    }

    for(int i=0; i<NOFCONSUMERS; i++) {
        consumer_ind[i] = (i + 1);
        pthread_create(&consumers[i], NULL, consumer, &consumer_ind[i]);
    }

    while(1) {

    }

    sem_destroy(&empty);
    sem_destroy(&mutex);
    sem_destroy(&full);

    return 0;
}