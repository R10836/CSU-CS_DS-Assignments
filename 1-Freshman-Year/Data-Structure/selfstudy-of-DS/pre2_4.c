//
// Created by 33712 on 2023/7/30.
//
//------------------链队列、不循环版--------------------
//照pre2_2改成链式存储（pre1_2）
//在我的自创写法中: p_sth《==》sth_ptr



#include <stdio.h>
#include <stdlib.h>



//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE (-1)
#define OVERFLOW (-2)



typedef int Status; //Status是函数的类型，其值是函数结果状态代码
typedef int ELemType; //ELemType是表里元素的类型
/*
typedef struct QNode {
    ELemType data;
    struct QNode* next;
} QNode, * QNode_Ptr;
typedef struct {
    QNode_Ptr front; //struct QNode*型
    QNode_Ptr rear;
} LinkQueue, * LinkQueue_ptr;
 */

//便于我的理解，可以写成：
struct QNode {
    //是链队列的结构体，用来表示整个链队列的基本信息。
    ELemType data;
    struct QNode* next;
};
typedef struct QNode QNode;
typedef struct QNode* QNode_ptr;

struct no_needed_name {
    //是链队列中的节点结构体，用来表示队列中的每个元素。
    struct QNode* front;
    struct QNode* rear;
    //由此看来，是struct QNode包含在struct no_needed_name之中，参照pre2_2相当于把struct QNode*当ELemType*用。
};
typedef struct no_needed_name LinkQueue;
typedef struct no_needed_name* LinkQueue_ptr;



//~构造一个空队列Q
Status InitQueue(LinkQueue_ptr LQ) {
    LQ->front = (struct QNode*) malloc(sizeof(struct QNode));
    if (LQ->front == NULL) return ERROR;
    LQ->front->next = NULL; //链式共性
    LQ->rear = LQ->front; //队列共性
    return OK;
}

//~销毁队列Q，Q不再存在
Status DestroyQueue(LinkQueue_ptr LQ) {
    struct QNode* bomb = LQ->front;
    while (bomb != NULL) {
        struct QNode* next_bomb = bomb->next;
        free(bomb);
        bomb = next_bomb;
    }
    LQ->front = NULL; // 确保 front 指向空，避免悬挂指针
    LQ->rear = NULL;  // 确保 rear 指向空，避免悬挂指针
    return OK;
}

//将Q清为空队列
Status ClearQueue() {
    ;
}

//~若队列Q为空队列，则返回TRUE，否则返回FALSE
Status QueueEmpty(LinkQueue_ptr LQ) {
    if (LQ->front == LQ->rear) return TRUE;
    else return FALSE;
}

//~返回Q的元素个数(不算头结点)，即为队列的长度
int QueueLength(LinkQueue_ptr LQ) {
    int sum = 0;
    struct QNode* p = LQ->front;
    while (p != LQ->rear) { //(不算头结点)
        p = p->next;
        sum++;
    }
    return sum;
}

//~若队列不空，则用e返回Q的队头元素，并返回OK；否则返回ERROR
ELemType GetHead(LinkQueue_ptr LQ) {
    if (LQ->front == LQ->rear) return ERROR;
    ELemType e = LQ->front->next->data;
    return e;
}

//~（入队）插入元素e为Q的新的队尾元素
Status EnQueue(LinkQueue_ptr LQ, ELemType e) {
    struct QNode* s = (struct QNode*) malloc(sizeof(struct QNode));
    if (s == NULL) return ERROR;
    //------核心-------
    s->data = e;
    s->next = NULL; //因为始终插在队尾，所以是null了
    LQ->rear->next = s; //将原来队尾指向null的指针指向s(断)
    LQ->rear = s; //将新的元素地址标记为rear
    //此时头结点（也是front指向的那个结点）不存放东西，之后的第一个结点才开始存，rear指向的那个结点存东西。
    //------核心-------
    return OK;
}

//~（出队）若队列不空，则删除Q的队头元素，用e返回其值.
ELemType DeQueue(LinkQueue_ptr LQ) {
    if (LQ->front == LQ->rear) return ERROR;
    struct QNode* p = LQ->front->next;
    ELemType e = p->data;
    LQ->front->next = p->next;
    if (LQ->rear == p) {
        LQ->rear = LQ->front;
    }
    free(p);
    return e;
}

//~从队头到队尾依此对队列Q中每个元素调用函数visit()。一旦visit失败，则操作失败。
Status QueueTraverse(LinkQueue_ptr LQ) {
    struct QNode* p = LQ->front->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

int main() {
    printf("------------------------------\n");

    LinkQueue LQ; //struct no_needed_name LQ;
    InitQueue(&LQ);
    printf("1 means empty, 0 means not empty, and the queue now is %d.\n", QueueEmpty(&LQ));
    EnQueue(&LQ, 111);
    EnQueue(&LQ, 222);
    EnQueue(&LQ, 333);
    EnQueue(&LQ, 444);
    EnQueue(&LQ, 555);
    QueueTraverse(&LQ);
    printf("there are %d elem in this queue.\n", QueueLength(&LQ));
    printf("the front is %d, the rear is %d.\n", LQ.front->next->data, LQ.rear->data);
    printf("let front %d out from this queue.\n", DeQueue(&LQ));
    QueueTraverse(&LQ);
    printf("there are %d elem in this queue.\n", QueueLength(&LQ));
    printf("now the front is %d.\n", GetHead(&LQ));
    printf("1 means empty, 0 means not empty, and the queue now is %d.\n", QueueEmpty(&LQ));
    printf("1 means DestroyQueue() success, 0 means not success, the DestroyQueue() now is %d.\n", DestroyQueue(&LQ));
//    QueueTraverse(&LQ);

    printf("------------------------------\n");
}