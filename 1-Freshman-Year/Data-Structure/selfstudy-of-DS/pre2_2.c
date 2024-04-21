//
// Created by 33712 on 2023/7/30.
//
//
// Created by 33712 on 2023/7/29.
//
//------------------queue--------------------
//自创版、



#include <stdio.h>
#include <stdlib.h>



//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE (-1)
#define OVERFLOW (-2)
#define QUEUE_INIT_SIZE 7 //存储空间的初始分配量
#define QUEUE_INCREMENT 10 //储空间的分配增量



typedef int Status; //Status是函数的类型，其值是函数结果状态代码
typedef int ELemType; //ELemType是表里元素的类型
typedef struct Queue {
    ELemType* front; //队头
    ELemType* rear; //队尾
    int queuesize; //当前已分配的存储空间，以元素为单位
} * p_SqQueue;
//typedef struct Queue SqQueue;
//typedef struct Queue* p_SqQueue;

//~《创》构造一个空队列Q。
Status InitQueue(p_SqQueue Q) {
    Q->front = (ELemType*) malloc(QUEUE_INIT_SIZE * sizeof(ELemType));
    if (Q->front == NULL) return ERROR;
    Q->rear = Q->front; //队尾指针和队首指针指向一个地方
    Q->queuesize = QUEUE_INIT_SIZE;
    return OK;
}

//《销》队列Q被销毁，不再存在。
Status DestroyQueue() {
    return OK;
}

//将Q清为空队列。
Status ClearQueue() {
    return OK;
}

//~若Q为空队列，则返回TRUE，否则FALSE。
Status QueueEmpty(p_SqQueue Q) {
    if (Q->rear == Q->front) return TRUE; //队尾指针和队首指针指向一个地方就是队列为空
    else return FALSE;
}

//自己加判满
Status QueueFull(p_SqQueue Q) {
    if (Q->rear - Q->front >= Q->queuesize - 1) return TRUE; //因为rear不存东西，所以size始终比实际存东西的格子多一个！故size-1
    else return FALSE;
}

//~返回Q的元素个数，即队列的长度。
int QueueLength(p_SqQueue Q) {
    if (Q->rear == Q->front) return ERROR; //若队列为空
    return (Q->rear - Q->front); //队尾和队首的差值就等于总共有多少个元素（ELemType*型的地址以一个ELemType型的元素为单位！）
}

//~《查》用e返回Q的队头元素。
ELemType GetHead(p_SqQueue Q) {
    if (Q->rear == Q->front) return ERROR;
    return *(Q->front); //front指向地址有内容所以不用加减1啥的
}

//~《增》插入元素e为Q的新的队尾元素。
Status EnQueue(p_SqQueue Q, ELemType e) {
    if (Q->rear - Q->front >= Q->queuesize - 1) { //队满
        Q->front = (ELemType*) realloc(Q->front, (Q->queuesize + QUEUE_INCREMENT) * sizeof(ELemType));
        if (Q->front == NULL) return ERROR;
        Q->rear = Q->front + Q->queuesize;
        Q->queuesize += QUEUE_INCREMENT;
    }
    *(Q->rear) = e; //rear指向的地址上的内容赋值为e
    Q->rear++; //rear在向上移动一个单位地址，故此时rear无内容！
    //现在rear指向的是最后入元素的地址（无内容，因为上移了）；front指向的是最先入元素的地址（有内容）。
    return OK;
}

//~《删》删除Q的队头元素，并用e返回其值。
ELemType DeQueue(p_SqQueue Q) {
    if (Q->rear == Q->front) return ERROR;
    ELemType e = *(Q->front); //e赋值为front指向的那个地址上的元素，因为front指向地址有内容所以不用加减1啥的
    Q->front++; //移动一个ELemType*型单位长度的地址
    return e;
}

//~从队头到队尾，依次对Q的每个数据元素调用函数visit()。一旦visit()失败，则操作失败。
Status QueueTraverse(p_SqQueue Q) {
    for (int i = 0; Q->front + i != Q->rear; i++) { //front即front[0]有内容。rear即front[?]无内容。所以是[front,rear)区间
        printf("%d ", Q->front[i]);
    }
    printf("\n");
    return OK;
}



int main() {
    printf("------------------------------\n");

    struct Queue Q;
    InitQueue(&Q);
    printf("1 means empty, 0 means not empty, so the queue now is %d.\n", QueueEmpty(&Q));
    EnQueue(&Q, 111);
    EnQueue(&Q, 222);
    EnQueue(&Q, 333);
    EnQueue(&Q, 444);
    EnQueue(&Q, 555);
    EnQueue(&Q, 666);
    printf("1 means full, 0 means not full, and the queue now is %d.\n", QueueFull(&Q));
    QueueTraverse(&Q);
    printf("use QueueLength(), queue's $used$ length is %d.\n", QueueLength(&Q));
    printf("now, front is %d.\n", *(Q.front));
    printf("now, rear is %d.\n", *(Q.rear - 1));
    printf("use DeQueue(), the deleted elem is %d.\n", DeQueue(&Q));
    QueueTraverse(&Q);
    printf("use DeQueue(), the deleted elem is %d.\n", DeQueue(&Q));
    QueueTraverse(&Q);
    printf("use GetHead(), front is %d.\n", GetHead(&Q));
    printf("use QueueLength(), queue's $used$ length is %d.\n", QueueLength(&Q));
    printf("1 means empty, 0 means not empty, so the queue now is %d.\n", QueueEmpty(&Q));

    printf("------------------------------\n");
}