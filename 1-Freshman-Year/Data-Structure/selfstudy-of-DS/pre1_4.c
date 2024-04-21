//
// Created by 33712 on 2023/7/29.
//
//------------------循环链（单/双）表--------------------

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

//~初始化双向循环链表
Status InitCirDuLinkList(DuLinkList L) {
    L->prev = L;
    L->next = L;
    return OK;
}

//判断循环双链表是否为空
Status ListEmpty(DuLinkList L) {
    if (L->next == L) return TRUE;
    else return FALSE;
}

//判断结点p是否为循环双链表的表尾结点
Status isTail (DuLinkList L, DuLNode* p) {
    if (p->next == L) return TRUE;
    else return FALSE;
}

//~双链表的插入；按位序插入（用头结点）,这是常用的
Status ListInsert(DuLinkList L, int index, ELemType e) {
    //在带头结点的双链循环线性表L中第i个位置之前插入元素e。
    if (index < 1) return ERROR;
    DuLNode* p;
    p = L;
    int j = 0;
    while (p->next != L && j < index - 1) {
        //循环找到第i-1个结点
        p = p->next;
        j++;
    }
    if (p == NULL) return ERROR;
    /*------核心（4句话顺序绝对不可变）-------*/
    DuLNode* s = (DuLNode*) malloc(sizeof(DuLNode));
    s->data = e;
    s->next = p->next;
    p->next->prev = s; //if(p->next != NULL)不需要了
    s->prev = p;
    p->next = s;
    /*------核心（4句话顺序绝对不可变）-------*/
    return OK;
}

//循环双链表的删除
Status DeleteNextDuLNode(DuLNode* p) {
    //删除p结点的《后继结点》
    if (p == NULL) return ERROR;
    DuLNode* q = p->next; //找到p的后继结点q
    if (q == NULL) return ERROR;
    p->next = q->next;
    q->next->prev = p;
    free(q);
    return OK;
}

//~依此对L的每个元素调用函数visit()。
Status ListTraverse(DuLinkList L/* , visit() */) {
    DuLNode* p;
    p = L->next;
    while (p != L) { //这里变动了
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

//~自创：可以倒序遍历了
Status Reverse_ListTraverse(DuLinkList L/* , visit() */) {
    DuLNode* p;
    p = L->prev;
    while (p != L) { //这里也有变动哦
        printf("%d ", p->data);
        p = p->prev;
    }
    printf("\n");
    return OK;
}

int main() {
    printf("------------------------------\n");

    DuLNode L;
    InitCirDuLinkList(&L);
    printf("1 means empty, 0 means not empty, so the list now is %d.\n", ListEmpty(&L));
    printf("1 means isTail, 0 means is not Tail, so the node now is %d.\n", isTail(&L, &L));
    ListInsert(&L, 1, 111);
    ListInsert(&L, 2, 222);
    ListInsert(&L, 3, 333);
    ListInsert(&L, 4, 444);
    ListInsert(&L, 5, 555);
    ListInsert(&L, 6, 666);
    printf("1 means isTail, 0 means is not Tail, so the node now is %d.\n", isTail(&L, &L));
    printf("1 means isTail, 0 means is not Tail, so the node now is %d.\n", isTail(&L, L.prev));
    ListTraverse(&L);
    DeleteNextDuLNode(L.next); //这样本质删的是：头结点的下一个结点之后的那个结点。。。
    ListTraverse(&L);
    Reverse_ListTraverse(&L);
    printf("1 means empty, 0 means not empty, so the list now is %d.\n", ListEmpty(&L));

    printf("------------------------------\n");
}