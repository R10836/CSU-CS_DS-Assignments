#include <malloc.h>
#include <stdio.h>

#define MaxSize 10
#define InitSize 10 // 动态顺序表的初始长度

// 静态分配
typedef struct {
    double data[MaxSize];
    int length;
} SqList;

// 动态分配
typedef struct {
    double *data; //指示动态分配数组的指针
    int MaxSize_2; // 顺序表的最大容量
    int length; //顺序表的当前长度
} SeqList;

// 初始化静态顺序表
void InitList(SqList L) {
    for (int i = 0; i < MaxSize; i++) {
        L.data[i] = 0;
    }
    L.length = 0;
}

// 初始化动态顺序表
void InitList_2(SeqList L) {
    L.data = (double*) malloc(InitSize * sizeof(int));
    L.MaxSize_2 = InitSize;
    L.length = 0;
}

// 增加动态数组的长度
void IncreaseSize(SeqList L, int len) {
    double * p = L.data;
    L.data = (double*) malloc((L.MaxSize_2 + len) * sizeof(int));
    for (int i = 0; i < L.length; i++) {
        L.data[i] = p[i];
    }
    L.MaxSize_2 = L.MaxSize_2 + len;
    free(p);
}

int main() {
//    SqList L1;
//    InitList(L1);

//    SeqList L2;
//    InitList_2(L2);
}