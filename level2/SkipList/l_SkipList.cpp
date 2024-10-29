#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
int const MAX_DEPTH=4;
typedef struct Node
{
    int data;
    vector<Node*> next;
    Node(int data):data(data){
        next.resize(MAX_DEPTH);
        for(int i=0 ; i<MAX_DEPTH ; i++){
            next[i]=nullptr;
        }
    }
}Node;


class SkipList{
private:
    Node* head;
    int ran_level(){
        int level=1;
        while(level<MAX_DEPTH && rand()%2){level++;}
        return level;
    }
public:
    SkipList(){
        head=new Node(0);
    }
    ~SkipList(){
        Node* p=head;
        Node* q=nullptr;
        while(p->next[0]!=nullptr){
            q=p->next[0];
            delete(p);
            p=q;
        }delete(p);
    }
    void insert(int data){
        if(data<0){
            cout<<"don't accept -num";
            exit(1);
        }
        int ins_level=ran_level();
        cout<<ins_level<<endl;
        vector<Node*> into_position ;
        into_position.resize(ins_level);
        for(int i=0;i<ins_level;i++){
            Node* cur=head;
            while(cur->next[i]!=nullptr && cur->next[i]->data<data){
                cur=cur->next[i];
            }
            into_position[i]=cur;
        }
        Node* node=new Node(data);
        for(int i=0;i<ins_level;i++){
            node->next[i]=into_position[i]->next[i];
            into_position[i]->next[i]=node;//不考虑变头的情况，以因为会极大影响查找时的简洁性，实际应用中可以有一个空头
        }
    }
    void find_through(int depth){
        Node* cur=head;
        cout<<depth<<":";
        while(cur->next[depth]!=nullptr){
            cout<<cur->data<<" ";
            cur=cur->next[depth];
        }
        cout<<cur->data<<" ";
        cout<<endl;
        if(depth>0){
            find_through(depth-1);
        }else{
            cout<<endl;
        }
    }
    void del(int key){
        Node* forward=nullptr;
        for(int i=0;i<MAX_DEPTH;i++){
            Node* cur=head;
            while(cur->next[i]!=nullptr && cur->next[i]->data!=key){
                cur=cur->next[i];
            }
            if(cur->next[i]!=nullptr && cur->next[i]->data==key){
                forward=cur->next[i];
                cur->next[i]=cur->next[i]->next[i];
            }
            
        }
        if(forward!=nullptr){
            delete(forward);
        }
        
    }
    void search(int key){
        Node* cur=head;
        int depth=MAX_DEPTH-1;
        while(depth>=0 && not(cur->next[depth]!=nullptr && cur->next[depth]->data==key)){
            if(cur->next[depth]==nullptr){
                depth--;
                continue;
            }
            if(cur->next[depth]->data<key){
                cur=cur->next[depth];
            }else{
                if(depth==0){
                    break;
                }
                depth-=1;
            }
        }
        if(cur->next[depth]!=nullptr && cur->next[depth]->data==key){
            cout<<"find it:"<<cur->next[depth];
        }else{
            cout<<"can't find it";
        }
    }
};
int main(){
    SkipList lst;
    srand(time(0));
    lst.insert(1);
    lst.insert(2);
    lst.insert(3);
    lst.insert(11);
    lst.insert(12);
    lst.insert(1323);
    lst.insert(5);
    lst.find_through(MAX_DEPTH-1);
    lst.del(12);
    lst.find_through(MAX_DEPTH-1);
    lst.search(11);
    return 0;
}