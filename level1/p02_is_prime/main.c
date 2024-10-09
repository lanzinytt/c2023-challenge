#include "is_prime.h"
_Bool is_prime(int n);

int main() {
    int n;
    scanf("%d",&n);
    if(is_prime(n)){
        printf("yes");
    }else{
        printf("no");
    }
    return 0;
}
