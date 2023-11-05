#include<stdio.h>
#include<stdlib.h>
int indexoffirst(int arrivaltime[], int nop){
    int index = -1;
    int mi = 10000000;
    for(int i=0; i<nop; i++){
        if((arrivaltime[i] != -1) && (arrivaltime[i] < mi)){
            mi = arrivaltime[i]; index = i;
        }
    }
    return index;
}

int maxi(int a, int b){
    if(a >= b){
        return a;
    }
    return b;
}

int main() {
    int nop; // number of processes 
    scanf("%d", &nop);
    int arrivaltime[nop]; int tempo[nop];
    int bursttime[nop];
    int executionqueue[nop];
    for(int i=0; i<nop; i++){
        scanf("%d", &arrivaltime[i]); 
        tempo[i] = arrivaltime[i];
    }
    for(int i=0; i<nop; i++){
        scanf("%d", &bursttime[i]);
    }
    int iter = 0;
    while(1) {
        int index = indexoffirst(tempo, nop);
        if(index == -1){
            break;
        }
        executionqueue[iter] = index; iter++;
        tempo[index] = -1;
    }
    int time = 0;
    int completiontime[nop];
    for(int i=0; i<nop; i++){
        time = maxi(time, arrivaltime[executionqueue[i]]);
        time += bursttime[executionqueue[i]];
        completiontime[executionqueue[i]] = time;
    }
    int turnaroundtime[nop];
    for(int i=0; i<nop; i++){
        turnaroundtime[i] = completiontime[i] - arrivaltime[i];
    }
    int waititme[nop];
    for(int i=0; i<nop; i++){
        waititme[i] = turnaroundtime[i] - bursttime[i];
    }
    int totalwait = 0;
    for(int i=0; i<nop; i++){
        totalwait += waititme[i];
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
        printf("%d ", waititme[i]);
    }
    printf("\n");
    printf("Total wait time is : %d\n", totalwait);
    printf("Average wait time is : %f\n", ((float)totalwait / (float)nop));
    return 0;
}