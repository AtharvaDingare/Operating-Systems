#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void arrayprint(int array[], int n) {
    for(int i=0; i<n; i++){
        printf("%d , ", array[i]);
    }
    printf("\n");
}

void bubblesort(int array[], int n) {
    for(int i=0; i<n; i++){
        for(int j=(i+1); j<n; j++){
            if(array[i] > array[j]){
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

int main() {
    printf("THIS IS THE PARENT PROCESS (PID : %d)\n", getpid());
    printf("PID : %d\n", getpid());
    printf("PPID : %d\n", getppid());

    int n;
    scanf("%d", &n);
    int array[n];
    for(int i=0; i<n; i++){
        scanf("%d", &array[i]);
    }

    int option;
    printf("MENU : \n");
    printf("1. NORMAL EXECUTION : \n");
    printf("2. ORPHAN PROCESS : \n");
    printf("3. ZOMBIE PROCESS : \n");

    scanf("%d", &option);

    switch (option)
    {
        case 1:
        {
            pid_t pid = fork();
            if(pid < 0){
                printf("FORK FAILED !\n");
                exit(1);
            }
            else if(pid == 0) {
                printf("THIS IS THE CHILD PROCESS \n PID : %d \n PPID : %d \n", getpid(), getppid());
                bubblesort(array,n);
                arrayprint(array,n);
                printf("child process ending now \n");
            }
            else{
                printf("THIS IS THE PARENT PROCESS (quick sort) (PID : %d)\n", getpid());
                wait(NULL);
                bubblesort(array,n);
                arrayprint(array,n);
                printf("PARENT PROCESS HAS NOW ENDED \n");
            }
            break;
        }
        case 2:
        {
            pid_t pid = fork();
            if(pid < 0) {
                printf("FORK FAILED !\n");
                exit(1);
            }
            else if(pid == 0) {
                printf("THIS IS THE CHILD PROCESS \n PID : %d \n PPID : %d \n", getpid(), getppid());
                sleep(10);
                printf("Parent process has already ended \n");
                printf("THIS IS THE CHILD PROCESS \n PID : %d \n PPID : %d \n", getpid(), getppid());
            }
            else{
                printf("This is the parent process \n PID : %d", getpid());
                sleep(5);

                system("ps -elf | grep -e 'PPID\\|CHILD'");
                printf("Parent process is ending , child process is still running \n");
            }
            break;
        }
        case 3:
        {
            pid_t pid = fork();
            if(pid < 0) {
                printf("FORK FAILED !\n");
                exit(1);
            }
            else if(pid == 0) {
                printf("This is the child process (zombie)\n");
                printf("PID : %d", getpid());
                printf("PPID : %d", getppid());

                printf("CHILD PROCESS ENDING NOW \n");
            }
            else{
                printf("THIS IS THE PARENT PROESS (PID : %d) \n", getpid());
                printf("THIS WILL GO TO SLEEP SO THAT CHILD BECOMES ZOMBIE\n");
                sleep(5);

                char command[100];
                sprintf(command, "ps -elf | grep %d", getpid());
                system(command);

                printf("PARENT PROCESS ENDING NOW \n");
            }
            break;
        }
        default:
        {
            printf("INVALID CHOICE \n");
            break;
        }
    }
}