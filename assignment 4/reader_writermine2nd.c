#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t wrt;
sem_t mutex;
int readercount = 0;
int nofwriters;
int nofreaders;

void *writer(void * arg) {
    int *ind = (int *)arg;

    printf("Writer %d is trying to write to database\n", (*ind));
    sem_wait(&wrt);
    printf("The writer %d is writing to the database\n", (*ind));
    sleep(3);
    sem_post(&wrt);
    printf("The writer %d is leaving the database\n", (*ind));
    pthread_exit(NULL);
}

void *reader(void *arg) {
    int *ind = (int *)arg;
    printf("The reader %d is trying to read from the database \n", (*ind));
    sem_wait(&mutex);
    readercount++;
    if(readercount == 1) {
        sem_wait(&wrt);
    }
    printf("The reader %d is reading from the database \n", (*ind));
    sem_post(&mutex);

    sem_wait(&mutex);
    readercount--;
    if(readercount == 0) {
        sem_post(&wrt);
    }
    printf("The reader %d is leaving from the database \n", (*ind));
    sem_post(&mutex);
    sleep(3);
    pthread_exit(NULL);
}

int main() {
    printf("START\n");
    printf("Enter the number of writers : \n");
    scanf("%d", &nofwriters);
    printf("Enter the number of readers : \n");
    scanf("%d", &nofreaders);
    pthread_t writers[nofwriters];
    pthread_t readers[nofreaders];
    int writers_ind[nofwriters];
    int readers_ind[nofreaders];
    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);

    for(int i=0; i<nofwriters; i++) {
        int *ind = malloc(sizeof(int));
        *ind = (i + 1);
        pthread_create(&writers[i], NULL, writer, (void *)ind);
    }

    for(int i=0; i<nofreaders; i++) {
        int *ind = malloc(sizeof(int));
        *ind = i+1;
        pthread_create(&readers[i], NULL, reader, (void *)ind);
    }

    for(int i=0; i<nofwriters; i++) {
        pthread_join(writers[i], NULL);
    }
    for(int i=0; i<nofreaders; i++) {
        pthread_join(readers[i], NULL);
    }

    sem_destroy(&wrt);
    sem_destroy(&mutex);
    return 0;
}