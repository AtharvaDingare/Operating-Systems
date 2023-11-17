#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void arrayprint(int arr[], int n){
    for(int i=0; i<n; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}



void bubblesort(int arr[], int n) {
    for(int i=0; i<n; i++){
        for(int j=(i+1); j<n; j++){
            if(arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void quicksort(int arr[], int n) {
    for(int i=0; i<n; i++){
        for(int j=(i+1); j<n; j++){
            if(arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main () {
    printf("This is the main process\n");
    printf("PID : %d\n", getpid());
    printf("PPID : %d\n", getppid());
    int n;
    scanf("%d", &n);
    int array[n];
    for(int i=0; i<n; i++){
        scanf("%d", &array[i]);
    }
    printf("Entered array is : [ ");
    for(int i=0; i<n; i++){
        printf("%d , ", array[i]);
    }
    printf(" ]\n");

    printf("MENU : \n");
    printf("1. NORMAL EXECUTION \n");
    printf("2. ORPHAN PROCESS \n");
    printf("3. ZOMBIE PROCESS \n");

    int choice;
    printf("Enter a number : \n");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
        {
            pid_t pid = fork();
            if(pid < 0) {
                printf("Fork failed \n");
                exit(1);
            }
            else if(pid == 0) {
                printf("Child process (BUBBLE SORT) started execution \n");
                printf("PID : %d\n", getpid());
                printf("PPID : %d\n", getppid());

                bubblesort(array,n);
                arrayprint(array,n);

                printf("Child process is ending \n");
            }
            else{
                printf("Parent process (QUICK SORT) started execution \n");
                printf("PID : %d\n", getpid());

                wait(NULL);

                printf("Child process has ended , this is the parent process \n");
                quicksort(array,n);
                arrayprint(array,n);
                printf("Parent proces ending \n");
            }
            break;
        }
        case 2:
        {
            pid_t pid = fork();
            if(pid < 0) {
                printf("Fork failed ! \n");
                exit(1);
            }
            else if(pid == 0) {
                printf("This is the child process \n");
                printf("PID : %d\n", getpid());
                printf("PPID : %d\n", getppid());

                sleep(10);

                printf("The child process is still running \n");
                printf("PID : %d\n", getpid());
                printf("PPID : %d\n", getppid());
            }
            else{
                printf("This is the parent process \n");
                printf("PID : %d\n", getpid());
                printf("The parent process will sleep \n");
                sleep(5);

                system("ps -elf | grep -e 'PPID\\|CHILD'"); // REMEMBER
                printf("Parent process is ending , child process is still running somewhere \n");
            }
            break;
        }
        case 3:
        {
            pid_t pid = fork();
            if(pid < 0) {
                printf("Fork failed \n");
                exit(1);
            }
            else if(pid == 0) {
                printf("Child process (Zombie) has begun \n");

                printf("Child process (PID : %d) ended \n", pid);
            }
            else{
                // sleep call done for child process to finish and become zombie
                sleep(5);

                char command[100];
                sprintf(command, "ps -elf | grep %d", getpid());
                system(command);

                printf("Parent process (PID : %d) now ending \n", getpid());
            }
        }
        default:
        {
            printf("INVALID CHOICE\n");
            break;
        }
    }
}
