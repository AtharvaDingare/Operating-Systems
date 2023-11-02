#include<stdio.h>

int recurse(int n, int m, int allocation[][m], int maxneed[][m], int total[], int available[], int remainingneed[][m], int check[]) {
    int baseflag = 1;
    // base case
    for(int i=0; i<n; i++){
        if(check[i] == 0) {
            baseflag = 0; break;
        }
    }
    if(baseflag == 1){
        return 1;
    }



    int finalflag = 0;
    for(int i=0; i<n; i++){

        if(check[i] == 1){
            continue;
        }

        int checkprocessflag = 1;
        for(int j=0; j<m; j++){
            if(available[j] < remainingneed[i][j]){
                checkprocessflag = 0; break;
            }
        }
        if(checkprocessflag == 1) {
            int availablerepeat[m];
            for(int j=0; j<m; j++){
                availablerepeat[j] = available[j] + allocation[i][j];
            }
            int checkrepeat[n];
            for(int j=0; j<n; j++){
                if(j == i){
                    checkrepeat[j] = 1;
                }
                else{
                    checkrepeat[j] = check[j];
                }
            }
            int recursiveflagcheck = recurse(n,m,allocation,maxneed,total,availablerepeat,remainingneed,checkrepeat);
            if(recursiveflagcheck == 1){
                finalflag = 1; break;
            }
        }
    }
    if(finalflag == 1){
        return 1;
    }
    else{
        return 0;
    }
}


void main() {
    int n,m;
    printf("Enter the number of processes\n");
    scanf("%d", &n);
    printf("Enter the number of resources\n");
    scanf("%d", &m);
    
    int allocation[n][m];
    printf("Please enter the allocated resources for each process\n");
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++){
            scanf("%d", &allocation[i][j]);
        }
    }
    int maxneed[n][m];
    printf("Please enter the max need of resources for each process\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%d", &maxneed[i][j]);
        }
    }
    
    int total[m];
    printf("Please enter each of the total available resource \n");
    for(int i=0; i<m; i++){
        scanf("%d", &total[i]);
    }
    
    int available[m];
    for(int i=0; i<m; i++){
        int sum = 0;
        for(int j=0; j<n; j++){
            sum += allocation[j][i];
        }
        available[i] = total[i] - sum;
    }
    int remainingneed[n][m];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            remainingneed[i][j] = maxneed[i][j] - allocation[i][j];
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            printf("%d ", remainingneed[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int check[n];
    for(int i=0; i<n; i++){
        check[i] = 0;
    }
    for(int i=0; i<m; i++){
        printf("%d ", available[i]);
    }
    printf("\n");
    int answer = recurse(n,m,allocation,maxneed,total,available,remainingneed,check);
    
    if(answer == 1){
        printf("There is no deadlock in the given arrangement\n");
    }
    else{
        printf("There is a deadlock present in the given arrangement\n");
    }
}