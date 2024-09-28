#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct Node {
    int data;           // 数据域
    struct Node* next;  // 指针域，指向下一个节点
} Node;// 创建新节点
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // 分配内存
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;  // 设置数据
    newNode->next = NULL;  // 新节点的下一个节点为空
    return newNode;
}// 在链表末尾插入新节点
void insertNode(Node** head, int data) {//此处head为头指针的位置，此处用head位置是为了能在函数中改变头指针
    Node* newNode = createNode(data);
    if (*head == NULL) {//*head表示head，head为无，则无头结点
        *head = newNode;  // 如果链表为空，新节点成为头节点
    } else {
        Node* temp = *head;//定义临时指针temp
        while (temp->next != NULL) {
            temp = temp->next;  // 移动到链表末尾
        }
        temp->next = newNode;  // 将新节点链接到链表末尾
    }
}// 打印链表
void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}int main() {
    Node* head = NULL;  // 初始化空链表

    insertNode(&head, 10);//head 是指向头的指针，&head是head的位置
    insertNode(&head, 20);
    insertNode(&head, 30);

    printf("Linked List: ");
    printList(head);

    // 释放链表内存
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
