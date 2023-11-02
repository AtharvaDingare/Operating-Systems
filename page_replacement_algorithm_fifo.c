#include<stdio.h>
#include<stdlib.h>

int main() {
    int nf;
    scanf("%d", &nf);
    int len;
    scanf("%d", &len);
    int currentindex = 0;
    int frames[nf];
    for(int i=0; i<nf; i++){
        frames[i] = -1;
    }
    int reference[len];
    int pagehit = 0, pagefault = 0;
    for(int i=0; i<len; i++){
        scanf("%d", &reference[i]);
        int flag = 0;
        for(int j=0; j<nf; j++){
            if(frames[j] == reference[i]){
                pagehit++; flag = 1; break;
            }
        }
        if(!flag){
            pagefault++;
            frames[currentindex] = reference[i];
            currentindex = (currentindex + 1) % nf;
        }
        printf("Frame State after iteration number %d \n", (i+1));
        for(int j=0; j<nf; j++){
            printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Total page hits are : \n%d \n", pagehit);
    printf("Total page faults are : \n%d \n", pagefault);
    printf("Hit ratio is : \n%f \n", ((float)pagehit / ((float)pagehit + (float)pagefault)));
    return 0;
}