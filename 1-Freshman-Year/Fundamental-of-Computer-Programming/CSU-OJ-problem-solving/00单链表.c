#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

struct Node* createHead();
struct Node* creatNode(int data);
void printList(struct Node* headNode);
void insertNodeByHead(struct Node* headNode, int data);
void insertNodeByTail(struct Node* headNode, int data);

//
int main()
{
    struct Node* list=createHead();  //创建链表
    for(int i=1; i<5; i++)
    {
        insertNodeByTail(list, i);
    }
    printList(list);
    system("pause");
    return 0;
}


//创建表头
struct Node* createHead()
{
    //结构体指针变成结构体变量--》通过动态内存申请: int a=(int)mallloc(参数)
    struct Node* headNode=(struct Node*)malloc(sizeof(struct Node));
    //变量使用前必须初始化
    headNode->next=NULL;//: a.next=空
    return headNode;//返回a
}

//创建节点--》把用户的数据变成结构体变量的样子
struct Node* creatNode(int data)
{
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->data=data;
    newNode->next=NULL;
    return newNode;
}

//番外：打印节点--》准备一个指针指向表头的下一个，判断有没有data，有则打印
void printList(struct Node* headNode)//打印哪个表，参数就是谁的表头
{
    struct Node* pMove=headNode->next;
    while(pMove!=NULL)
    {
        printf("%d\t",pMove->data);
        pMove=pMove->next;
    }
    printf("\n");
}

//在头节点后插入节点（头插法）
void insertNodeByHead(struct Node* headNode, int data)
{
    //把数据变成结构体变量
    struct Node* newNode=creatNode(data);

    newNode->next=headNode->next;   //先让新节点的指针指向旧节点
    headNode->next=newNode;         //再让头节点的指针指向新节点，二者不可颠倒
}

//（尾插法）
void insertNodeByTail(struct Node* headNode, int data)
{
    struct Node* newNode=creatNode(data);
    struct Node* tailNode;
    if(data==/*若data为初值，则tailNode=headnode，否则则一直在最后令tailNode=newNode*/1)
    {
        tailNode=headNode;
    }
    newNode->next=NULL;
    tailNode->next=newNode;
    tailNode=newNode;
}

//
// void insertNodeByTrall(struct Node *List,int data)
// {
//     struct Node *lastNode = endofList(List);
//     struct Node *newNode  = createNode(data);
//     lastNode->next = newNode;
// }
// struct Node* endofList(struct Node *List)
// {
//     while(List->next) List = List->next;
//     return List;
// }