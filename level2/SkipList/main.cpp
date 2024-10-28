#include <iostream>
#include <ctime>
const int MAX_DEPTH=4;

typedef struct _Node{
    int data;
    int depth;
    struct _Node* next;
    struct _Node* down;
}Node;

class Skiplist{
private:
    Node* head[MAX_DEPTH];
    int Depth;

    int rand_dep(){
        int Ap_depth=0;
        while(Ap_depth<MAX_DEPTH && rand()%2){Ap_depth++;}
        return Ap_depth;
    }
    Node* create_node(int data,int depth){
        Node* new_node=new Node;
        new_node->data=data;
        new_node->depth=depth;
        new_node->next=nullptr;
        new_node->down=nullptr;
        if(new_node==nullptr){
            std::cout<<"Failed";
            exit(1);
        }
        return new_node;
    }
    Node* find_key(int key,Node* st){
        Node* temp=st;
        while(temp->data!=key && temp->next!=nullptr&& temp->next->data<key){
            temp=temp->next;
        }
        return temp;
    }
    Node* into_layer(int dep,int data,Node* down){
        Node* temp = create_node(data,dep);
        Node* cur=head[dep];
        if(head[dep]->data>data){
            temp->next = head[dep];
            head[dep]=temp;
        }else{
            while(cur->next!=nullptr && cur->next->data<data){
                cur=cur->next;
            }
            temp->next=cur->next;
            cur->next=temp;
        }
        temp->down=down;
        return temp;
    }

public:

    Skiplist(){
        Depth=0;
        for(int i=0;i<MAX_DEPTH;i++){
            head[i]=create_node(0,i);
        }
    }

    void insert(int data){
        int insert_depth=rand_dep();
        if(insert_depth>Depth+1){
            insert_depth=Depth+1;
            Depth+=1;
        }
        Node* down =nullptr;
        for(int i=0;i<=insert_depth;i++){
            down = into_layer(i,data,down);
        }
        
    }
    
    void search(int data){
        int tdep=Depth;
        Node* cur=head[tdep];
        while(tdep>=0){
            while(data>=head[0]->data && data<=head[tdep]->data){
                tdep--;
                cur=head[tdep];
            }
            find_key(data,cur);
            if(cur->data!=data){
                cur=cur->down;
                tdep--;
            }else{
                std::cout<<"find it:"<<cur;
                break;
            }
        }
        std::cout<<"not find";
    }
};


int main(){
    srand(time(0));
    Skiplist lst;
    lst.insert(1);
    lst.insert(4);
    lst.insert(5);
    lst.insert(3);
    lst.insert(2);
    lst.search(2);
}