#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>

void arrayprint(int arr[], int n) {
    for(int i=0; i<n; i++) {
        printf("%d , ", arr[i]);
    }
    printf("\n");
}

void bubblesort(int arr[], int n) {
    for(int i=0; i<n; i++) {
        for(int j=(i+1); j<n; j++){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
}

int main() {
    printf("This is the main process \n");
    printf("PID : %d\n", getpid());

    int n;
    scanf("%d", &n);
    int array[n];
    for(int i=0; i<n; i++){
        scanf("%d", &array[i]);
    }

    arrayprint(array,n);
    bubblesort(array,n);
    arrayprint(array,n);
    pid_t child;
    child = fork();

    if(child < 0) {
        printf("Fork failed !\n");
        exit(1);
    }
    else if(child == 0) {
        printf("THIS IS THE CHILD PROCESS \n (PID : %d) \n (PPID : %d) \n", getpid() , getppid());
        char *args[n + 2];
        args[0] = "./2bchildmine";
        for(int i=0; i<n; i++) {
            char buffer[10];
            snprintf(buffer, sizeof(buffer),"%d",array[i]);
            args[i+1] = strdup(buffer);
        }
        args[n+1] = NULL;
        execve(args[0], args, NULL);
        perror("execve");
        printf("The execve command failed , please check child process \n");
        return 1;
    }
    else{
        printf("THIS IS THE PARENT PROCESS (PID : %d) \n", getpid());
        wait(NULL);
        printf("PARENT PROCESS COMPLETED \n");
    }
    return 0;
}