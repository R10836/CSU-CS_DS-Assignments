//
// Created by 33712 on 2023/7/29.
//
//------------------双向链表（双链表）-------------------

#include <stdio.h>
#include <stdlib.h>



#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE (-1)
#define OVERFLOW (-2)



typedef int Status; //Status是函数的类型，其值是函数结果状态代码
typedef int ELemType; //ELemType是表里元素的类型
struct DuLNode {
    ELemType data; //数据域
    struct DuLNode* prev; //前驱指针
    struct DuLNode* next; //后继指针
};
typedef struct DuLNode DuLNode;
typedef struct DuLNode* DuLinkList;



//~初始化双向链表
Status InitDuLinkList(DuLinkList L) {
    //不知道为什么不能malloc!!!
//    L = (DuLNode*) malloc(sizeof(DuLNode)); //分配一个头结点
//    if (L == NULL) return ERROR;
    //前驱指针后继指针都设为NULL
    L->prev = NULL;
    L->next = NULL;
    return OK;
}

//~判断双链表是否为空（带头结点）
Status ListEmpty(DuLinkList L) {
    if (L->next == NULL) return 1;
    else return 0;
}

//~按位序插入（用头结点）,这是常用的
Status ListInsert(DuLinkList L, int index, ELemType e) {
    //在带头结点的双链循环线性表L中第i个位置之前插入元素e。
    if (index < 1) return ERROR;
    DuLNode* p;
    p = L;
    int j = 0;
    while (p->next != NULL && j < index - 1) {
        //循环找到第i-1个结点
        p = p->next;
        j++;
    }
    if (p == NULL) return ERROR;
    /*------核心（4句话顺序绝对不可变）-------*/
    DuLNode* s = (DuLNode*) malloc(sizeof(DuLNode));
    s->data = e;
    s->next = p->next;
    if(p->next != NULL)
        p->next->prev = s;
    s->prev = p;
    p->next = s;
    /*------核心（4句话顺序绝对不可变）-------*/
    return OK;
}

//双链表的插入(后插操作)
Status InsertNextDuLNode(DuLNode* p, DuLNode* s) {
    //在p结点之后插入s结点
    if (p == NULL || s == NULL) return ERROR;
    /*------核心（4句话顺序绝对不可变）-------*/
    //假设有结点a、p、c，在pc之间插s
    s->next = p->next; //_1_
    if(p->next != NULL)
        p->next->prev = s; //_2_
    s->prev = p; //_3_
    p->next = s; //_4_
    /*------（4句话顺序绝对不可变）------*/
    return OK;
}

//双链表的删除
Status DeleteNextDuLNode(DuLNode* p) {
    //删除p结点的后继结点
    if (p == NULL) return ERROR;
    DuLNode* q = p->next; //找到p的后继结点q
    if (q == NULL) return ERROR;
    p->next = q->next;
    if (q->next != NULL) { //q结点不是最后一个结点
        q->next->prev = p;
    }
    free(q);
    return OK;
}

//销毁双链表
Status Destroy(DuLinkList L) {
    //循环释放各个数据结点
    while (L->next != NULL) {
        DeleteNextDuLNode(L);
    }
    free(L);
    L = NULL;
    return OK;
}

//~依此对L的每个元素调用函数visit()。
Status ListTraverse(DuLinkList L/* , visit() */) {
    DuLNode* p;
    p = L->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

//~自创：倒序遍历(先循环到最后一个元素，再往前走，非常墨迹!!!)
Status Reverse_ListTraverse(DuLinkList L/* , visit() */) {
    DuLNode* p = L;
    while (p->next != NULL) {
        p = p->next;
    }
    while (p->prev != NULL) { //头结点不打印，所以这里略有变动
        printf("%d ", p->data);
        p = p->prev;
    }
    printf("\n");
    return OK;
}

int main() {
    printf("------------------------------\n");

    DuLNode L;
    InitDuLinkList(&L);
    printf("1 means empty, 0 means not empty, so the list now is %d.\n", ListEmpty(&L));
    ListInsert(&L, 1, 111);
    ListInsert(&L, 2, 222);
    ListInsert(&L, 3, 333);
    ListInsert(&L, 4, 444);
    ListInsert(&L, 5, 555);
    ListTraverse(&L);
    Reverse_ListTraverse(&L);

    printf("------------------------------\n");
}