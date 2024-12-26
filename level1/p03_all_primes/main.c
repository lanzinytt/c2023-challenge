#include <stdio.h>
#include <time.h>

int main() {
    time_t st,ed;
    st=clock();
    int arr[1001]={0};
    int cur=1;
    while(cur<1000){
        cur++;
        if(arr[cur] == 1){
            continue;
        }
        else{
            for(int i=cur;i<1001;i+=cur){
                arr[i]=1;
            }
        }
        printf("%d ",cur);
        
    }

    printf("\n");
    ed=clock();
    printf("%f",(double)(ed-st));
    return 0;
}