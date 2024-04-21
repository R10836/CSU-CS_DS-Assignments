//
// Created by 33712 on 2023/7/30.
//
//------------------循环队列--------------------
//自创版、
//现在rear指向的是最后入元素的地址（无内容，因为上移了）；front指向的是最先入元素的地址（有内容）。
//为什么要取模？？？虽然rear和front相对差值还是那么的，但因为rear一直++到一个超过size的数，无法在内存上实现循环
//要想取模，得大改。因为指针指针只能进行加法和减法运算，没有乘法、除法、取余运算！ struct CirQueue的rear和front不能再是指针类型了。



#include <stdio.h>
#include <stdlib.h>



//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE (-1)
#define OVERFLOW (-2)
#define MAXSIZE 6


typedef int Status; //Status是函数的类型，其值是函数结果状态代码
typedef int ELemType; //ELemType是表里元素的类型
typedef struct CirQueue {
    ELemType* base; //初始化的动态分配存储空间
    int front; //头指针，若队列不空，指向队列头元素
    int rear; //尾指针，若队列不空，指向队列尾元素的下一个位置
} * p_SqCirQueue;



//~《创》构造一个空队列Q。
Status InitCirQueue(p_SqCirQueue CQ) {
    CQ->base = (ELemType*) malloc(MAXSIZE * sizeof(ELemType));
    if (CQ->base == NULL) return ERROR;
    CQ->front = CQ->rear = 0;
    return OK;
}

//《销》队列Q被销毁，不再存在。
Status DestroyCirQueue() {
    return OK;
}

//将Q清为空队列。
Status ClearCirQueue() {
    return OK;
}

//~若Q为空队列，则返回TRUE，否则FALSE。
Status CirQueueEmpty(p_SqCirQueue CQ) {
    //法1：牺牲一个单元
    //法2：结构体里增设表示当前元素个数的数据成员
    //法3：结构体里增设tag数据成员巴拉巴拉
    //这里采用：法1
    if (CQ->rear == CQ->front) return TRUE; //队尾指针和队首指针指向一个地方就是队列为空
    else return FALSE;
}

//自加，判满
Status CirQueueFull(p_SqCirQueue CQ) {
    //真实存值的单位始终比size小1个单位，所以满了意味着真实存值的单位再加1个单位就达到了size
    if ( (CQ->rear + 1) % MAXSIZE == CQ->front ) return TRUE;
    else return FALSE;
}

//~返回Q的元素个数，即队列的长度。
int CirQueueLength(p_SqCirQueue CQ) {
    return ( CQ->rear - CQ->front + MAXSIZE ) % MAXSIZE; //取模
}

//~《查》用e返回Q的队头元素。
ELemType GetHead(p_SqCirQueue CQ) {
    if (CQ->rear == CQ->front) return ERROR;
    return CQ->base[CQ->front]; //front指向地址有内容所以不用加减1啥的
}

//~《增》插入元素e为Q的新的队尾元素。
Status EnCirQueue(p_SqCirQueue CQ, ELemType e) {
    if ( (CQ->rear + 1) % MAXSIZE == CQ->front) return ERROR;
    CQ->base[CQ->rear] = e;
    CQ->rear = (CQ->rear + 1) % MAXSIZE; //取模！！！
    //现在rear指向的是最后入元素的地址（无内容，因为上移了）；front指向的是最先入元素的地址（有内容）。
    return OK;
}

//~《删》删除Q的队头元素，并用e返回其值。
ELemType DeCirQueue(p_SqCirQueue CQ) {
    if (CQ->rear == CQ->front) return ERROR;
    ELemType e = CQ->base[CQ->front]; //e赋值为front指向的那个地址上的元素，因为front指向地址有内容所以不用加减1啥的
    CQ->front = (CQ->front + 1) % MAXSIZE; //取模！！！
    return e;
}

//~从队头到队尾，依次对Q的每个数据元素调用函数visit()。一旦visit()失败，则操作失败。
Status CirQueueTraverse(p_SqCirQueue CQ) {
    int len = ( CQ->rear - CQ->front + MAXSIZE ) % MAXSIZE;
    int now;
    for (int i = 0; i < len; i++) { //front有内容。rear无内容。所以是[front,rear)区间循环len次
        now = (CQ->front + i) % MAXSIZE; //还得取模！
        printf("%d ", CQ->base[now]);
    }
    printf("\n");
    return OK;
}



int main() {
    printf("------------------------------\n");

    struct CirQueue CQ;
    InitCirQueue(&CQ);
    printf("1 means empty, 0 means not empty, and the queue now is %d.\n", CirQueueEmpty(&CQ));
    EnCirQueue(&CQ, 111);
    EnCirQueue(&CQ, 222);
    EnCirQueue(&CQ, 333);
    EnCirQueue(&CQ, 444);
    EnCirQueue(&CQ, 555);
    CirQueueTraverse(&CQ);
    printf("the front is %d, the rear is %d.\n", CQ.base[CQ.front], CQ.base[CQ.rear - 1]);
    printf("the length of the circled queue is %d.\n", CirQueueLength(&CQ));
    printf("1 means full, 0 means not full, and the queue now is %d.\n", CirQueueFull(&CQ));
    printf("-----------\n");
    printf("now delete the front of the queue elem %d.\n", DeCirQueue(&CQ)); CirQueueTraverse(&CQ);
    EnCirQueue(&CQ, 666); CirQueueTraverse(&CQ);
    printf("now delete the front of the queue elem %d.\n", DeCirQueue(&CQ)); CirQueueTraverse(&CQ);
    EnCirQueue(&CQ, 777); CirQueueTraverse(&CQ);
    printf("now delete the front of the queue elem %d.\n", DeCirQueue(&CQ)); CirQueueTraverse(&CQ);
    EnCirQueue(&CQ, 888); CirQueueTraverse(&CQ);
    printf("now delete the front of the queue elem %d.\n", DeCirQueue(&CQ)); CirQueueTraverse(&CQ);
    EnCirQueue(&CQ, 999); CirQueueTraverse(&CQ);
    printf("now delete the front of the queue elem %d.\n", DeCirQueue(&CQ)); CirQueueTraverse(&CQ);
    EnCirQueue(&CQ, 101010); CirQueueTraverse(&CQ);
    printf("now delete the front of the queue elem %d.\n", DeCirQueue(&CQ)); CirQueueTraverse(&CQ);
    printf("-----------\n");
    printf("1 means empty, 0 means not empty, and the queue now is %d.\n", CirQueueEmpty(&CQ));
    printf("1 means full, 0 means not full, and the queue now is %d.\n", CirQueueFull(&CQ));
    printf("get the front of the queue, is %d.\n", GetHead(&CQ));

    printf("------------------------------\n");
}