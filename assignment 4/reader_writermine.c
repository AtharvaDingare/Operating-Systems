#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

sem_t wrt;
sem_t mutex;
int readercount = 0;
int nofwriters;
int nofreaders;

void *writer(void * temp) {
    int *idptr = (int *)temp;
    int id = *idptr;
    printf("Writer %d is trying to write to the database \n", id);
    sem_wait(&wrt);
    printf("Writer %d is writing to database \n", id);
    sleep(3);
    sem_post(&wrt);
    printf("Writer %d exits \n", id);

    pthread_exit(NULL);
}

void *reader(void * temp) {
    int *idptr = (int *)temp;
    int id = *idptr;
    printf("Reader %d is trying to read from the database \n", id);
    sem_wait(&mutex);
    readercount ++;
    if(readercount == 1)
        sem_wait(&wrt);
    sem_post(&mutex);
    printf("Reader %d is reading from the database \n", id);
    
    sem_wait(&mutex);
    readercount--;
    if(readercount == 0)
        sem_post(&wrt);
    sem_post(&mutex);
    printf("Reader %d has left the database \n", id);
    sleep(3);
    pthread_exit(NULL);
}


int main() {
    printf("START\n");
    printf("Enter the number of writers : \n");
    scanf("%d", &nofwriters);
    printf("Enter the number of readers : \n");
    scanf("%d", &nofreaders);
    pthread_t writers[nofwriters + 1];
    pthread_t readers[nofreaders + 1];
    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);
    for(int i=1; i<=nofwriters; i++) {
        int *writer_id = malloc(sizeof(int));
        *writer_id = i;
        pthread_create(&writers[i], NULL, writer, (void *)writer_id);
    }

    for(int i=1; i<=nofreaders; i++) {
        int *reader_id = malloc(sizeof(int));
        *reader_id = i;
        pthread_create(&readers[i], NULL, reader, (void *)reader_id);
    }

    for(int i=1; i<=nofwriters; i++) {
        pthread_join(writers[i], NULL);
    }

    for(int i=1; i<=nofreaders; i++) {
        pthread_join(readers[i], NULL);
    }

    sem_destroy(&wrt);
    sem_destroy(&mutex);

    pthread_exit(NULL);

}