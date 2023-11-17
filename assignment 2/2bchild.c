#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid = fork();

    printf("\nChild process started.");
    printf("\nPID: %d", getpid());
    
    int i = argc - 1;
    printf("\n\nREVERSED ARRAY:");
    printf("\n[%s,", argv[i]);
    for (int i = argc - 2; i > 1; i--)
    {
        printf(" %s,", argv[i]);
    }
    printf(" %s]", argv[1]);
    printf("\n");

    return 0;
}