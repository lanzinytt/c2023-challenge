#include <stdio.h>
int main() {
    int arr[101]={0};
    int lst[50]={0};
    int cur=1,acc=0;
    while(cur<100){
        cur++;
        if(arr[cur] == 1){
            continue;
        }
        else{
            lst[acc]=cur;
            for(int i=cur;i<101;i+=cur){
                arr[i]=1;
            }
        }
        acc++;
    }
    int m[100]={0};
    for(int i=0;i<acc;i++){
        for(int j=i;j<acc;j++){
            if(lst[i]+lst[j]<100 && m[lst[i]+lst[j]]==0){
                m[lst[i]+lst[j]]=1;
                printf("%d + %d =%d\n",lst[i],lst[j],lst[i]+lst[j]);
            }
        }
    }
    int flag=0;
    for(int i=4;i<100;i+=2){
        if(m[i]==0){
            flag+=1;
        }
    }
    if(flag==0){
        printf("correct!");
    }
    return 0;
}