#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50
#define MIN 0
void Bsort(int arr[],int n){
    for(int x=0;x<n;x++){
        for(int y=0;y<(n-x-1);y++){
            if(arr[y]<arr[y+1]){
                int temp=arr[y];
                arr[y]=arr[y+1];
                arr[y+1]=temp;
            }
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int range=MAX-MIN+1;
    int lst[n];
    srand(time(NULL));
    for(int i=0;i<n;i++)
    {   
        lst[i]=rand()%range +MIN;
    }
    for(int i=0;i<n-1;i++)
    {
        printf("%d ",lst[i]);
    }
     printf("%d\t",lst[n-1]);
    Bsort(lst,n);
    for(int i=0;i<n;i++)
    {
        printf("%d ",lst[i]);
    }
    return 0;
}