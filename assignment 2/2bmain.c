#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Function to print an Array
void printArray(int arr[], int n)
{
    int i;
    printf("\n[%d,", arr[0]);
    for (int i = 1; i < n - 1; i++)
        printf(" %d,", arr[i]);
    printf(" %d]", arr[n - 1]);
}

// Quick Sort
void quickSort(int arr[100], int first, int last)
{

    int i, j, k, pivot, cmp = 0, swap = 0, temp;

    if (first < last)
    {
        pivot = first;
        i = first;
        j = last;

        while (i < j)
        {
            while (arr[i] <= arr[pivot] && i < last)
                i++;

            while (arr[j] > arr[pivot])
                j--;

            cmp++;
            if (i < j)
            {
                swap++;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        temp = arr[pivot];
        arr[pivot] = arr[j];
        arr[j] = temp;

        quickSort(arr, first, j - 1);
        quickSort(arr, j + 1, last);
    }
}

int main()
{
    // Main process starts
    printf("\nThis is the main process.");
    printf("\nPID: %d", getpid());
    printf(" | PPID: %d", getppid());

    int n;
    printf("\n\nEnter the number of integers to sort: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter the %d integers: ", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("\nENTERED ARRAY:");
    printArray(arr, n);

    printf("\n\nSORTED ARRAY (using Quick Sort):");
    quickSort(arr, 0, n - 1);
    printArray(arr, n);

    pid_t child;
    // Fork System call
    child = fork();

    if (child < 0)
    {
        // Failed Fork
        printf("\nFork failed.");
        exit(1);
    }
    else if (child == 0)
    {
        // Inside Child Process
        
        char *args[n + 2];
        args[0] = "./2bchild";
        for (int i = 0; i < n; i++)
        {
            char buffer[10];
            snprintf(buffer, sizeof(buffer), "%d", arr[i]); // converts int to string format and pass them into the buffer
                args[i + 1] = strdup(buffer);           // strdup:- (string duplicate) create a new copy of the string
        }
        args[n + 1] = NULL; // indicate the end of the list of command-line arguments.
        execve(args[0], args, NULL);
        perror("execve");
        printf("Main process (PID: %d) ends.\n", getpid());
        return 1;
    }
    else
    {
        // Inside parent process
        printf("\n\nParent process started.");
        printf("\nPID: %d", getpid());
        printf("\nChild PID: %d", child);

        printf("\n\n");
        wait(NULL);

        printf("\n\nParent process executed successfully.");

        return 0;
    }
}