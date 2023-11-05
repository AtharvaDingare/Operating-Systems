#include<stdio.h>
#include<stdlib.h>

int pickoptimal(int arrivaltime[], int bursttime[], int time, int nop){
    int index = -1;
    int mi = 100000000;
    for(int i=0; i<nop; i++){
        if((arrivaltime[i] <= time) && (arrivaltime[i] != -1)){
            if(bursttime[i] < mi){
                mi = bursttime[i];
                index = i;
            }
        }
    }
    return index;
}

int maxi(int a , int b){
    if(a >= b){
        return a;
    }
    return b;
}

int mini(int a, int b){
    if(a <= b){
        return a;
    }
    return b;
}

int main(){
    int nop;
    scanf("%d", &nop);
    int arrivaltime[nop]; int tempo1[nop];
    for(int i=0; i<nop; i++){
        scanf("%d", &arrivaltime[i]);
        tempo1[i] = arrivaltime[i];
    }
    int bursttime[nop]; int tempo2[nop];
    for(int i=0; i<nop; i++){
        scanf("%d", &bursttime[i]);
        tempo2[i] = bursttime[i];
    }
    int completiontime[nop];
    int turnaroundtime[nop];
    int waittime[nop];
    int executionqueue[1000]; int timespanqueue[1000]; int iter = 0;
    int timequantum;
    scanf("%d", &timequantum);
    int time = 0;
    //printf("All okay ?");
    
    while(1) {
        int index = pickoptimal(tempo1, tempo2, time, nop);
        if(index == -1){
            break;
        }
        time = maxi(time, arrivaltime[index]);
        if(tempo2[index] > timequantum){
            tempo2[index] -= timequantum;
            executionqueue[iter] = index;
            timespanqueue[iter] = timequantum;
            time += timequantum;
            iter++;
        }
        else{
            executionqueue[iter] = index;
            timespanqueue[iter] = tempo2[index];
            tempo2[index] = 0;
            tempo1[index] = -1;
            time += timespanqueue[iter];
            completiontime[index] = time;
            iter++;
        }
    }
    for(int i=0; i<nop; i++){
        turnaroundtime[i] = completiontime[i] - arrivaltime[i];
    }
    int totalwait = 0;
    for(int i=0; i<nop; i++){
        waittime[i] = turnaroundtime[i] - bursttime[i];
        totalwait += waittime[i];
    }
    printf("The completion time of each process : \n");
    for(int i=0; i<nop; i++){
        printf("%d ", completiontime[i]);
    }
    printf("\n");
    printf("The turn around time of each process : \n");
    for(int i=0; i<nop; i++){
        printf("%d ", turnaroundtime[i]);
    }
    printf("\n");
    printf("The wait time of each process : \n");
    for(int i=0; i<nop; i++){
        printf("%d ", waittime[i]);
    }
    printf("\n");
    printf("Total wait time is : %d\n", totalwait);
    printf("Average wait time is : %f\n", (float)(totalwait)/(float)(nop));
    
    return 0;
}