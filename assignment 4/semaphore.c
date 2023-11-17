#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 2

int buffer[BUFFER_SIZE];
sem_t empty, full, mutex;

int in = 0;
int out = 0;

long long current_timestamp()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (ts.tv_sec * 1000000000LL + ts.tv_nsec); // Convert to nanoseconds
}

void *producer(void *arg)
{
    int item;
    while (1)
    {
        long long start_time = current_timestamp(); // Start measuring execution time in nanoseconds

        item = rand() % 100; // Produce an item (e.g., a random number)

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;

        printf("Producer %d produced item: %d\n", *((int *)arg), item);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);

        long long end_time = current_timestamp(); // Stop measuring execution time in nanoseconds
        long long execution_time = end_time - start_time;
        printf("Producer %d execution time: %lld nanoseconds\n", *((int *)arg), execution_time);

        sleep(1); // Simulate slower producer
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int item;
    while (1)
    {
        long long start_time = current_timestamp(); // Start measuring execution time in nanoseconds

        sem_wait(&full);
        sem_wait(&mutex);

        item = buffer[out];

        printf("Consumer %d consumed item: %d\n", *((int *)arg), item);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);

        long long end_time = current_timestamp(); // Stop measuring execution time in nanoseconds
        long long execution_time = end_time - start_time;
        printf("Consumer %d execution time: %lld nanoseconds\n", *((int *)arg), execution_time);

        sleep(2); // Simulate slower consumer
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];
    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        producer_ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        consumer_ids[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    while (1)
    {
        // The main thread can perform other tasks or have additional control logic here.
        // For simplicity, we just let the producer and consumer threads run indefinitely.
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}