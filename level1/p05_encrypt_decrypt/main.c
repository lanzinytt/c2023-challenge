#include <stdio.h>

char jude_char(char str){
    if(str<='z' && str>='a'){
        return 'a';
    }else if(str<='Z' && str>='A'){
        return 'A';
    }
}

void encrypt(char lst[] ,int step){
    int i=0;
    while(lst[i] !='\0'){
        char base=jude_char(lst[i]);
        int tim=0;
        while((lst[i]-base+step+26*tim)<0){
            tim++;
        }
        lst[i]=(lst[i]-base+step+26*tim)%26 +base;
        i++;
    }
}

int main() {
    char str[]="hello";
    int step;
    scanf("%d",&step);
    encrypt(str,step);
    printf("%s\n",str);
    encrypt(str,-step);
    printf("%s",str);    
}



