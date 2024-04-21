#include<stdio.h>
#include<stdlib.h>

void add2list(struct node *list, int n);

struct node
{
    int data;
    struct node *next;//说明next(地址)能够存储一个指向struct node类型的指针
}headnode;

int main()
{
    int n,m;
    while(scanf("%d",&n)!=EOF)
    {
        scanf("%d",&m);
        while(n--)
        {
            void add2list(heanoed, n);
        }

        struct node *p;
        while(1)
        {
            p+=m;
            printf("%d",*p);
        }
    }
    return 0;
}

//在 地址whichnode 后面插入新的链表，其值为thing
void add2list(struct node *whichnode, int thing)
{
    /*需要配合：使用
    struct node
    {
    int data;
    struct node *next;
    };
    */
    struct node *newnode;
    newnode=malloc(sizeof(struct node));
    if(newnode==NULL){exit(EXIT_FAILURE);}//不用管这句干啥
    newnode->data=thing;
    newnode->next=whichnode;
    *whichnode=*newnode;
}