#include <stdio.h>
#include <stdlib.h>

typedef struct Lst {
    int data;
    struct Lst* next;
}Lst;
Lst* create(int data){
    Lst* Node =(Lst*)malloc(sizeof(Lst));
    if (Node == NULL){
        printf("fail!!!");
        exit(1);
    }
    Node->data=data;
    Node->next=NULL;
    return Node;
}
void insert(int data,Lst** head){
    Lst* in_Node=create(data);
    if(*head==NULL){
        *head=in_Node;
    }
    else{
        Lst* temp=*head;
        while (temp->next != NULL){
            temp=temp->next;
        }
        temp->next=in_Node;
    }
}
void print_th(int th,Lst* head){
    int tim=1;
    Lst* temp=head;
    while(tim!=th && temp->next!=NULL){
        temp=temp->next;
        tim++;
    }
    if(tim==th){
        printf("%d",temp->data);
    }else{
        printf("the th has problem!");
    }
    printf("\n");

}
void print_al(Lst* head){
    Lst* temp =head;
    printf("%d",temp->data);
    while((temp->next) != NULL){
        temp=temp->next;
        printf("->%d",temp->data);
    }
    printf("\n");
}
int main() {
    Lst* head=NULL;
    insert(20,&head);
    insert(30,&head);
    insert(30,&head);insert(30,&head);insert(30,&head);
    insert(30,&head);
    print_al(head);
    print_th(2,head);
    print_th(114514,head);
    return 0;
}