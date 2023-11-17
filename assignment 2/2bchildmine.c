#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main(int argc, char * argv[]) {
    printf("This is the CHILD PROCESS\n (PID : %d)\n (PPID : %d)\n", getpid(), getppid());
    int ite = argc-1;
    printf("[ %s , ", argv[ite]);
    for(ite = argc-2; ite > 1; ite--) {
        printf("%s , ", argv[ite]);
    }
    printf("%s ] \n", argv[ite]);
    printf("CHILD PROCESS COMPLETED \n");
    return 0;
}