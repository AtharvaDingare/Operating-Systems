#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<unistd.h>

int main() {
    key_t key = ftok(".", 'aaa');
    printf("Generated key : %d\n", key);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    printf("The shared memory id is : %d\n", shmid);
    char * str = shmat(shmid, (void *)0, 0);
    printf("Address of shared memory is : %p\n", (void *)str);

    printf("Obtained string is : %s\n", str);
    return 0;
}