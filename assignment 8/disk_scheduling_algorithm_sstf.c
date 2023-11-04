#include<stdio.h>

int abss(int a, int b) {
    if(a >= b) {
        return (a-b);
    }
    return (b-a);
}


int main() {
    int nofdisks; // total number of tracks
    scanf("%d", &nofdisks);
    int nr; // size of request queue
    scanf("%d", &nr);
    int requestqueue[nr];
    for(int i=0; i<nr; i++) {
        scanf("%d", &requestqueue[i]);
    }
    int curpos; // current postion of head
    scanf("%d", &curpos);
    int timetocoveronetrack;
    scanf("%d", &timetocoveronetrack);
    int visited[nofdisks]; // keeps a track of which tracks are already visited and which are left by 0 and 1
    for(int i=0; i<nofdisks; i++) {
        visited[i] = 0; // initially nothing is visited
    }
    visited[curpos] = 1; // current position is visited

    int order[nr + 1]; // this array denotes the order in which we travel through the request queue
    order[0] = curpos; // currently the 0th node is current position , now we begin
    int current = curpos;
    int iter = 1; // iterator at which next element to be inserted
    while(1) {
        int index = -1; // which element to be inserted 
        int min_val = 100000000;
        for(int i=0; i<nr; i++) {
            if(visited[requestqueue[i]] == 0) {
                int absolute = abss(current , requestqueue[i]);
                if(absolute < min_val) {
                    min_val = absolute;
                    index = i;
                }
            }
        }
        if(index == -1) {
            break; // this means that we have visited all the possible elements in request queue
        }
        else{
            // we insert element at index to iter
            order[iter] = requestqueue[index];
            iter++;
            visited[requestqueue[index]] = 1; // as we are done with that element we turn it on in visited array
            current = requestqueue[index]; // as we have now moved to a new track inside the disk
        }
    }

    // at the end we get the order array which is the flow of our algorithm , our answer will be sum of all adjecent values 
    int ans = 0;
    for(int i=1; i<=nr; i++) {
        ans += abss(order[i] , order[i-1]);
    }
    for(int i=0; i<=nr; i++) {
        printf("At the %dth iteration , the track is : %d \n", (i+1),order[i]);
    }
    printf("The total number of track movements are : %d \n", ans);
    printf("The total amount of time taken for entire shit to happen is : %d \n", ans * timetocoveronetrack);
    return 0;
}