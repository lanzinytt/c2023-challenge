#include <stdio.h>
#include <stdbool.h>
#include <math.h>
_Bool is_prime(int n){
    int ran=pow(n,0.5);
    _Bool flag=true;
    if(n<=3){
        return flag;
    }
    if(n%2==0){
        return not flag;
    }
    for(int i=3;i<ran+1;i+=2){
        if(n%i==0){
            return false;
        }
    }
    return true;
}