#include<stdio.h>
#include<stdlib.h>

int pickoptimal(int arrivaltime[], int bursttime[], int time, int nop) {
    int index = -1;
    int mi = 100000000;
    for(int i=0; i<nop; i++){
        if((arrivaltime[i] <= time) && (arrivaltime[i] != -1)){
            if(bursttime[i] < mi) {
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

int main() {
    int nop;
    scanf("%d", &nop);
    int arrivaltime[nop]; int tempo[nop];
    for(int i=0; i<nop; i++){
        scanf("%d", &arrivaltime[i]);
        tempo[i] = arrivaltime[i];
    }
    int bursttime[nop];
    for(int i=0; i<nop; i++){
        scanf("%d", &bursttime[i]);
    }
    int turnaroundtime[nop];
    int completiontime[nop];
    int waittime[nop];
    int executionqueue[nop]; int iter = 0;
    int time = 0;
    while(1) {
        int index = pickoptimal(tempo, bursttime, time, nop);
        if(index == -1){
            break;
        }
        time = maxi(time, arrivaltime[index]);
        executionqueue[iter] = index; iter++;
        time += bursttime[index];
        tempo[index] = -1;
    }
    time = 0;
    for(int i=0; i<nop; i++){
        time = maxi(time, arrivaltime[executionqueue[i]]);
        time += bursttime[executionqueue[i]];
        completiontime[executionqueue[i]] = time;
    }
    for(int i=0; i<nop; i++){
        turnaroundtime[i] = completiontime[i] - arrivaltime[i];
    }
    for(int i=0; i<nop; i++){
        waittime[i] = turnaroundtime[i] - bursttime[i];
    }
    int totalwait = 0;
    for(int i=0; i<nop; i++){
        totalwait += waittime[i];
    }
    printf("Completion time : \n");
    for(int i=0; i<nop; i++){
        printf("%d ", completiontime[i]);
    }
    printf("\n");
    printf("Turn around time : \n");
    for(int i=0; i<nop; i++){
        printf("%d ", turnaroundtime[i]);
    }
    printf("\n");
    printf("Wait time : \n");
    for(int i=0; i<nop; i++){
        printf("%d ", waittime[i]);
    }
    printf("\n");
    printf("Total wait time is : %d\n", totalwait);
    printf("Average wait time is : %f\n", ((float)totalwait / (float)nop));
    return 0;
}