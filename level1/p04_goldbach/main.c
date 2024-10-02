#include <stdio.h>
int find_key(int key,int arr[]){
    int cur=0;
    int i;
    for(i=2;i<101;i++){
        if(arr[i]==0){
            cur++;
        }
        if(cur==key){
            return i;
        }
    }
    return 1;
}
int main() {
    int arr[101]={0};
    int cur=1,acc=0;
    while(cur<100){
        cur++;
        if(arr[cur] == 1){
            continue;
        }
        else{
            for(int i=cur;i<101;i+=cur){
                arr[i]=1;
            }
        }
        acc++;
    }
    int lst[101]={0};
    int get_i,get_j,res;
    for(int i=2;i<=acc;i++){
        for(int j=i+1;j<acc;j++){
            get_i=find_key(i,arr);
            get_j=find_key(j,arr);
            res=get_i+get_j;
            if(res<101 && lst[res]==0){
                printf("%d + %d =%d",get_i,get_j,res);
                lst[res]=1;
            }
        }
    }
    return 0;
}//未完待续。。