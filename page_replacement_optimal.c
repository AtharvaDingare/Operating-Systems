#include<stdio.h>

int main() {
    int nf;
    scanf("%d", &nf);
    int len;
    scanf("%d", &len);
    int frames[nf];
    for(int i=0; i<nf; i++) {
        frames[i] = -1;
    }
    int reference[len];
    for(int i=0; i<len; i++) {
        scanf("%d", &reference[i]);
    }
    // usual input till this point
    int pagehit = 0;
    int pagefault = 0;
    for(int i=0; i<len; i++) {
        int index = -1; // where should replacement be done ? (0 <= index <= (nf-1))
        int flag = 0; // to check if current integer is present in frames 
        for(int j=0; j<nf; j++) {
            if(reference[i] == frames[j]){
                flag = 1; break; // integer present in frames 
            }
        }
        if(flag) {
            pagehit ++;
            printf("Frame State after iteration number %d \n", (i+1));
            for(int j=0; j<nf; j++){
                printf("%d ", frames[j]);
            }
            printf("\n");
            continue;
        }
        else{
            pagefault ++;
            // first check if any index in frames in empty (not utilised yet) (-1)
            int flag2 = 0;
            for(int i=0; i<nf; i++) {
                if(frames[i] == -1) {
                    flag2 = 1;
                    index = i; break;
                }
            }
            if(flag2){
                // this means some index was -1
                // replace that index 
                frames[index] = reference[i];
                printf("Frame State after iteration number %d \n", (i+1));
                for(int j=0; j<nf; j++){
                    printf("%d ", frames[j]);
                }
                printf("\n");
                continue;
            }
            // if no index is -1 , we need to search the reference string after the current index for the index that appears last
            // there is a way to do this in O(logn) but for simplicity lets just use 2 simple for loops (anyways doesnt matter if we reduce TC or not we need the final answer)
            int max_index = -1000000;
            for(int ite1=0; ite1 < nf; ite1++) {
                // this loop travels all elements in our frame
                int where = -1;
                for(int ite2=(i+1); ite2<len; ite2++) {
                    // this loop travels (for each element in the frame) every element after the current index in reference string
                    if(reference[ite2] == frames[ite1]){
                        where = ite2;
                        break;
                    }
                }
                if(where == -1){
                    // this means that element was never found after that position which means it is optimal to replace it
                    index = ite1; break;
                }
                else{
                    // this means element was found at some position and we want the maximum of such positions so
                    if(where > max_index) {
                        max_index = where;
                        index = ite1;
                    }
                }
            }
            // now those 2 for loops will do their job and calculate index , we just need to replace at that index 
            frames[index] = reference[i];
        }
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


    /*
    NOTE -:
    IN THIS ALGO THE FRAME STATE MAY NOT BE SAME AS THE VDO SOLUTION YOU ARE SEEING BCOZ AT SOME STEP THERE ARE MULTIPLE OPTIMAL CHOICES HENCE THERE ARE MULTIPLE WAYS A SOLUTION 
    CAN BE FORMED IG ??
    BUT PAGE HITS AND PAGE FAULTS MUST BE SAME
    */
}