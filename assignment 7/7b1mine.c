#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/ipc.h>

int main() {
    key_t key = ftok(".", 'aaa');
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    printf("The shared memory id is : %d\n", shmid);
    char * str = shmat(shmid, (void *)0, 0);
    printf("Shared memory address is : %p\n", (void *) str);
    printf("Enter the data : \n");
    gets(str);
    printf("Obtained data : %s", str);
    shmdt(str);
    return 0;
}