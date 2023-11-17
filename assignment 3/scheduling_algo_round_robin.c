#include<stdlib.h>
#include<stdio.h>

int main() {
    int nop;
    scanf("%d", nop);
    int arrivaltime[nop];
    for(int i=0; i<nop; i++){
        scanf("%d", arrivaltime[i]);
    }
    int bursttime[nop];
    for(int i=0; i<nop; i++){
        scanf("%d", bursttime[i]);
    }
    int timequantum;
    scanf("%d", timequantum);
    
    return 0;
} 