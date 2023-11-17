#include<stdio.h>
 
void main()
{
     
    // Taking Input - NumberofProcess, Arival Time, Burst Time, Time Quantum
     
    int nop;
    printf("\n\n Enter Number of Process:");
    scanf("%d",&nop);
 
    int at[nop],bt[nop],temp[nop];
     
    for(int i=0;i<nop;i++)
    {
        printf("\n\nEnter arival time and burst time of the process %d \n",i+1);
        scanf("%d",&at[i]);
        scanf("%d",&bt[i]);
 
        // Storing Burst Time in temp array    
        temp[i] = bt[i];
    }
     
    int time;
    printf("\n\n Enter Time Quantum:");
    scanf("%d",&time);
 
    // Using Round Robin Algoritm
    float avg_wt,avg_tat,wt=0,tat=0;
    int y = nop;
    int sum,count,i;
 
    printf("\n P \t AT \t BT \t TAT \t WT\n");
 
     
    sum = 0; // Storing burst time;
    i = 0; // For Pointing The Current Process
 
    while(y!=0)
    {
        // Checking if Process can complete in this Time Quantum
        if(temp[i] <= time && temp[i]>0)
        {
            sum = sum+temp[i]; // Storing Burst Time
            temp[i] = 0; // Process Complete
            count = 1;  // like flag to check process complete
        }
        // If Process take more time than 1 Time Quantum
        else if(temp[i] > 0)
        {
            temp[i] = temp[i] - time; // Decrementing the Quantum Time from Burst Time
            sum = sum + time; 
        }
 
        // If Process Completes
        if(temp[i] == 0 && count == 1)
        {
            y--; // Decrementing Process Counter
             
            printf("\n\n %d \t %d \t %d\t %d\t %d",i+1,at[i],bt[i],sum-at[i],sum-at[i]-bt[i]);
             
            // TurnAroundTime = ExitTime - ArrivalTime
            // Waiting time = TurnAroundTime - BurstTime
            wt = wt + sum - at[i] - bt[i]; // Total waiting time
            tat = tat + sum -at[i]; // Total Burst Time 
            count = 0;   // Resetting Flag
        }
 
        // printf("\n Current Index %d  Arrival Time %d  Remaining Burst Time %d",i,at[i],temp[i]);
 
        // If All Process Visited, then Run it in round robin fashion 
        if(i == nop-1)
        {
            i=0;
        }
        else if(at[i+1] <= sum) // Checking if next process is arrived or not
        {
            i++;
        }
        // If process is not in end and the next process has not arrived yet so start the remaining process again 
        else   
        {
            i = 0;
        }
    }
 
 
    // Calculating Average TurnAroundTime and Waiting Time
    avg_tat = tat/nop;
    avg_wt = wt/nop;
     
    printf("\n\n Average TurnAround Time: %f",avg_tat);
    printf("\n\n Average Waiting Time: %f\n",avg_wt);
}
/*
Input.txt File:
5
 
0 15
3 8
8 2
10 11
16 4
 
3
*/
