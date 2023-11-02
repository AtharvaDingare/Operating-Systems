#include<stdio.h>
#include<stdlib.h>

int main() {
    int nf;
    scanf("%d", &nf);
    int len;
    scanf("%d", &len);
    int frames[nf];
    for(int i=0; i<nf; i++){
        frames[i] = -1;
    }
    int reference[len]; // this is the reference string to be taken as input
    int pagehit = 0; // number of page hits
    int pagefault = 0; // number of page faults
    int storeindexes[100000]; // this array will store the indexes and as a new element comes we will update its index when it occured so that every time we know what is least recently used
    for(int i=0; i<100000; i++) {
        storeindexes[i] = -1; // initially no index has occured so -1
    }
    for(int i=0; i<len; i++) {
        scanf("%d", &reference[i]);
        int flag = 0;
        for(int j=0; j<nf; j++) {
            if(frames[j] == reference[i]) {
                // if you find the reference integer (integer in string) in one of the frames then its page hit
                pagehit++; flag = 1; break;
            }
        }
        if(!flag) {
            // if page hit did not occur then its page fault 
            pagefault++;
            int min_index = 100000000; // we want to calculate value at min_index
            int element = -1; // we want to calculate this
            int index = -1; // we need to change at this position
            for(int j=0; j<nf; j++) {
                if(storeindexes[frames[j]] < min_index) {
                    // if last time frames[i] occured is less than already calculated min_index value then we will update our element as now it is the 'least' recently used
                    min_index = storeindexes[frames[j]]; 
                    element = frames[j];
                    index = j;
                }
            }
            // at the end of the day we need to change at corrosponding position
            frames[index] = reference[i];
        }
        storeindexes[reference[i]] = i; // update the last time an element has occured
        printf("Frame State after iteration number %d \n", (i+1));
        for(int j=0; j<nf; j++){
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Number of page hits are : \n%d \n", pagehit);
    printf("Number of page faults are : \n%d \n", pagefault);
    printf("Hit ratio is : \n%f \n", ((float)pagehit/((float)pagefault + (float)pagehit)));
    return 0;
}