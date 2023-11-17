#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Function to print an Array
void printArray(int arr[], int n)
{
    int i;
    printf("\n[");
    printf("%d,", arr[0]);
    for (int i = 1; i < n - 1; i++)
        printf(" %d,", arr[i]);
    printf(" %d]", arr[n - 1]);
}

// Bubble Sort
void bubbleSort(int arr[], int n)
{
    int temp, i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Quick Sort
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    // Variable declarations
    int n, i, choice;

    // Main process starts
    printf("\nThis is the main process.");
    printf("\nPID: %d", getpid());
    printf(" | PPID: %d", getppid());

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

    printf("\n\n-------- MENU --------\n");
    printf("1 - Normal Execution (Fork & Wait)\n");
    printf("2 - Orphan Process\n");
    printf("3 - Zombie Process\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            // Failed Fork
            printf("Fork failed.\n");
            exit(1);
        }
        else if (pid == 0)
        {
            // Inside Child Process
            printf("\nChild process (Bubble Sort) started.");
            printf("\nPID: %d", getpid());
            printf("\nPPID: %d\n", getppid());
            bubbleSort(arr, n);

            printf("\nSorted array by the child process (Bubble Sort):");
            printArray(arr, n);

            printf("\n\nChild process executed successfully.\n");
        }
        else
        {
            // Inside Parent Process
            printf("\nParent process (Quick Sort) started.\nIt'll wait for the child process to complete.");
            printf("\nPID: %d", getpid());
            
            wait(NULL);

            printf("\n\nSorted array by the parent process (Quick Sort):");
            quickSort(arr, 0, n-1);
            printArray(arr, n);

            printf("\n\nChild process has completed. This is the parent process.");
            printf("\nParent process executed successfully.");
        }
        break;
    }
    case 2:
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            printf("Fork failed.\n");
            exit(1);
        }
        else if (pid == 0)
        {
            // Orphan process
            printf("\nOrphan process started (PID: %d).\n", getpid());
            printf("Parent process (PID: %d) terminated before the child process.\n", getppid());

            // Sleep to create an orphan process
            sleep(10);

            printf("\nOrphan process (PID: %d) completed.\n", getpid());
        }
        else
        {
            // Parent process
            printf("\nParent process (PID: %d) started.\n", getpid());

            // Sleep to simulate some processing time before exiting
            sleep(5);
            system("ps -elf | grep -e 'PPID\\|CHILD'");

            printf("Parent process (PID: %d) completed.\n", getpid());
        }
        break;
    }
    case 3:
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            printf("Fork failed.\n");
            exit(1);
        }
        else if (pid == 0)
        {
            // Child process
            printf("\nChild process (Zombie) started.");

            printf("\nChild process (PID: %d) completed.\n", getpid());
        }
        else
        {
            // Parent process
            // Sleep to allow the child process to complete first
            sleep(5);

            char command[100];
            sprintf(command, "ps -elf | grep %d", getpid());
            system(command);

            printf("\nParent process (Zombie) started.\n");
            printf("Parent process will sleep to create a zombie (PID: %d).\n", getpid());

            printf("Parent process (PID: %d) completed.\n", getpid());
        }
        break;
    }
    default:
        printf("Invalid choice.\n");
        break;
    }

    return 0;
}