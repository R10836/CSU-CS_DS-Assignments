//
// Created by 33712 on 2023/7/27.
//
//------------------线性表的链式表示-------------------
//index=0时是头结点！

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
struct LNode {
    ELemType data;
    struct LNode* next;
};
typedef struct LNode LNode;
typedef struct LNode* LinkList; /* 替代c++的引用。。。现在代表了指向struct List结构体的指针类型 */
/*
struct LNode {
    ELemType data;
    struct LNode* next;
};
typedef struct LNode LNode;
typedef struct LNode* LinkList;

等价于

struct LNode {
    ELemType data;
    struct LNode* next;
} LNode， * LinkList;
 */
// LNode* 从人类视角看强调的是一个结点
// LinkList 从人类视角看强调的是一个单链表


//~初始化一个单链表，带头结点
Status InitLinkList(LinkList L) {
    //初始化不要malloc，我也不知道为什么，写伪代码还行，C语言不行！
//    L = (LNode*) malloc(sizeof(LNode)); //分配一个头结点
//    if (L == NULL) return ERROR;
    L->next = NULL;  //头结点之后暂时还没有结点，且头结点不要存数据。
    L->data = 12580;
    return OK;
}

//~判断单链表是否为空
Status ListEmpty(LinkList L) {
    if (L->next == NULL) return 1;
    else return 0;
}

//~返回L中数据元素个数。
int ListLength(LinkList L) {
    LNode* p;
    p = L;
    int j = 0;
    while (p->next != NULL) {
        p = p->next;
        j++;
    }
    return j;
}

//按位序插入（不用头结点）
Status ListInsert_NotUsedHeadNode(LinkList L, int index, ELemType e) {
    //在第i个位置插入元素e
    if (index < 1) return ERROR;
    if (index == 1) {
        //-----麻烦就麻烦在,需要额外考虑第1个结点;其他都一样-----
        LNode* s = (LNode*) malloc(sizeof(LNode));
        s->data = e;
        s->next = L;
        L = s; //新结点成为头指针
        return OK;
    }
    LNode* p = L;
    int j = 0;
    while (p != NULL && j < index -1) {
        p = p->next;
        j++;
    }
    if (p == NULL) return ERROR;
    LNode* s = (LNode*) malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

//~按位序插入（用头结点）,这是常用的
Status ListInsert(LinkList L, int index, ELemType e) {
    //在第i个位置插入元素e
    if (index < 1) return ERROR; //1. 插入的是第0、-1、-2···位置的元素要报错
    LNode* p; //定义一个指针p，用于指向当前扫描到的结点
    p = L; //让p指向的和L指向的是同一个地方，L指向的是头结点，目前是头结点
    int j = 0; //j用于记录指针p指向的是第几个结点，目前是头结点即第0个结点
    while (p != NULL && j < index -1) {
        //循环找到第i-1个结点
        p = p->next;
        j++;
    }
    if (p == NULL) return ERROR; //2. 若index超过链表长度，要报错，而此时p指向的是空值
    /* -----核心----- */
    LNode* s = (LNode*) malloc(sizeof(LNode)); //强调！我个人觉得s按结点来理解比较好
    s->data = e;
    s->next = p->next; //让该位置的新结点的下一个地址，指向该位置的旧结点原来指向的那个下一个地址
    p->next = s; //将结点s连到p指向的那个结点之后。
    /* -----核心----- */
    return OK;
}

//~按位序删除（用头结点）,这是常用的
Status ListDelete(LinkList L, int index) {
    if (index < 1) return ERROR;
    LNode* p;
    p = L;
    int j = 0;
    while (p != NULL && j < index -1) {
        p = p->next;
        j++;
    }
    if (p == NULL) return ERROR;
    //首先，记录一下删除结点的信息（不可或缺！）
    LNode* q = p->next;
    ELemType e = q->data;
    printf("the deleted node's data is %d.\n", e);
    //之后，将删除结点之前的那个结点指针指向删除结点之后的那个结点
    p->next = q->next;
    //最后，释放被删除结点的资源
    free(q);
    return OK;
}

//指定结点的后插操作
Status InsertNextNode(LNode *p, ELemType e) {
    //后插操作：在p结点之后插入元素
    if (p == NULL) return ERROR;
    LNode* s =(LNode*) malloc(sizeof(LNode));
    if (s == NULL) return ERROR;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

//指定结点的前插操作
Status InsertPriorNode(LNode* p, ELemType e) {
    //前插操作：在p结点之前插入元素(偷梁换柱，本质是让元素跑路而不是结点跑路)
    if (p == NULL) return ERROR;
    LNode* s = (LNode*) malloc(sizeof(LNode));
    if (s == NULL) return ERROR;
    //先实现一个后插
     s->next = p->next;
     p->next = s;
     //再偷梁换柱，让元素跑路
     s->data = p->data;
     p->data = e;
    return OK;
}

//指定结点的删除
Status DeleteNode(LNode* p) {
    //wang dao p13 21:00
    ;
    return OK;
}

//~按位查找（！！！如果没有怎么办！！！）
LNode* GetElem(LinkList L, int index) {
    if (index < 0) return NULL;
    LNode* p; //指针p指向当前扫描到的结点
    p = L; //L指向头结点，头结点是第0个结点
    int j = 0; //当前p指向的是第几个结点
    while (p != NULL && j < index) {
        //循环找到第i个结点
        p = p->next;
        j++;
    }
    return p;
}

//~按值查找（！！！如果没有怎么办！！！）
int LocateElem(LinkList L, ELemType e) {
    //我改版后返回的是位序，原版返回的是指针p而无法得知位序。
    LNode* p;
    p = L->next; //！这里忽视头结点，直接访问正文
    int j = 0+1;
    while (p != NULL && p->data != e) {
        p = p->next;
        j++;
    }
    return j;
}

//~依此对L的每个元素调用函数visit()。
Status ListTraverse(LinkList L/* , visit() */) {
    LNode* p;
    p = L->next; //！这里忽视头结点，直接访问正文
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

//---------

//~尾插法建立单链表
Status List_TailInsert (LinkList L, int len) {
    //即正向建立单链表(自加len用于设置链表的长度)
    InitLinkList(L); //初始化链表
    LNode* r = L; //初始化表尾指针r
    ELemType e;
    for (int i = 0; i < len; i++) {
        printf("please input your data:");
        scanf("%d", &e);
        InsertNextNode(r, e);
        r = r->next; //r始终指向表尾结点
    }
    return OK;
}

//~头插法建立单链表
Status List_HeadInsert(LinkList L, int len) {
    //即逆向建立单链表(自加len用于设置链表的长度)
    InitLinkList(L); //初始化链表
    LNode* s; ELemType e;
    for (int i = 0; i < len; i++) {
        printf("please input your data:");
        scanf("%d", &e);
        s = (LNode*) malloc(sizeof(LNode));
        s->data = e;
        s->next = L->next;
        L->next = s;
    }
    return OK;
}

//p31
void MergeList_L(LinkList La, LinkList Lb, LinkList Lc) {
    ;
}

int main() {
    printf("------------------------------\n");

    LNode L;
    InitLinkList(&L);
    printf("%d", L.data);
    printf("1 means empty, 0 means not empty, so the list now is %d.\n", ListEmpty(&L));
    ListInsert(&L, 1, 111);
    ListInsert(&L, 2, 222);
    ListInsert(&L, 3, 333);
    ListInsert(&L, 4, 444);
    ListInsert(&L, 5, 555);
    ListTraverse(&L);
    ListInsert(&L, 6, 818);
    ListTraverse(&L);
    printf("now ListLength is %d.\n", ListLength(&L));
    ListDelete(&L, 4);
    ListTraverse(&L);
    printf("selected by index is %d.\n", GetElem(&L, 2)->data);
    printf("selected by data is %d.\n", LocateElem(&L, 123));

    LNode L1;
    List_TailInsert(&L1, 6);
    ListTraverse(&L1);

    LNode L2;
    List_HeadInsert(&L2, 5);
    ListTraverse(&L2);

    printf("------------------------------\n");
}