#include <stdio.h>

char b1(int x) {
    if (x > 10) {
        return 'F';
    } else {
        return 'G';
    }
}

int j1(int x){
    if(x==0){
        return 0;
    }
    else if (x>0)
    {
        return 1; 
    }
    else if (x<0)
    {
        return -1;
    }

int j2(int x,int y){
    return 1-(x%y);
}
int j3(int x){
    if(x%4==0){
        if(x%400==0){
            return 1;
        }
        if(x%100==0){
            return 0;
        }
        return 1;
    }
}

}
int main(){
    int cont;
    scanf("%d",&cont);
    switch (cont)
    {
    case 1:
        int x; 
        char result;
        scanf("%d",&x);
        result=j1(x);
        printf("%c",result);
        break;
    
    default:
        break;
    }
    return 0;
}