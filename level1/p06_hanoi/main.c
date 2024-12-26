#include <stdio.h>
void hanno(int num,char st,char ex,char ed);

int main() {
    int n;
    scanf("%d",&n);
    
    hanno(n,'A','B','C');
    
    return 0;
}
void hanno(int num,char st,char ex,char ed){
    if(num==1){
        printf("%c->%c\n",st,ed);
    }else{
        hanno(num-1,st,ed,ex);
        hanno(1,st,ex,ed);
        hanno(num-1,ex,st,ed);
    }
}