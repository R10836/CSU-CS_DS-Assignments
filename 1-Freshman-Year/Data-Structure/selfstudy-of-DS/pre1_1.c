//https://chat.openai.com/share/f9384761-e05e-4d35-bae2-9356490f2a94
//
// Created by 33712 on 2023/7/27.
//
//线性表的顺序实现
//------------------线性表的动态分配顺序结构-------------------

#include <stdio.h>
#include <malloc.h>



#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE (-1)
#define OVERFLOW (-2)
#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量
#define LIST_INCREMENT 10 //线性表存储空间的分配增量



typedef int Status; //Status是函数的类型，其值是函数结果状态代码
typedef int ELemType; //ELemType是表里元素的类型
struct List {
    ELemType* elem; //存储空间基址
    int length; //当前长度
    int listsize; //当前分配的存储容量(以一个sizeof(ElemType)为单位)
};
typedef struct List SqList;
typedef struct List* p_SqList; /* 替代c++的引用。。。现在代表了指向struct List结构体的指针类型 */



//~构造一个空的线性表L。
Status InitList(p_SqList L) {
    L->elem = malloc(LIST_INIT_SIZE * sizeof(ELemType)); /* malloc返回的是指向这一片存储空间开始地点的指针；所以arr这个ele*型的变量 为 指向malloc申请出来空间的开始地点的指针 */
    if (L->elem == NULL) return ERROR; /* 需要判断:如果申请的结果为NULL的话表示内存空间申请失败 */
    L->length = 0; //空表长度为0
    L->listsize = LIST_INIT_SIZE; //初始存储容量
    return OK;
}

//销毁线性表L。
Status DestroyList(p_SqList L) {
    return OK;
}

//将L置为空表。
Status ClearList(p_SqList L) {
    return OK;
}

//若L是空表，返回TRUE，否则返回FALSE。
Status ListEmpty(SqList L) {
    return OK;
}

//~返回L中数据元素个数。
int ListLength(p_SqList L) {
    return L->length;
}

//~用e返回L中第i个元素的值。(由位置得元素)
ELemType GetElem(SqList L, int index, const ELemType* e) {
    if (index < 1 || index > L.length) {
        return ERROR;
    }
    e = &L.elem[index -1];
    return *e;
}

//~返回L中第1个与e满足compare()关系的元素位序。(由元素得位置)
int LocateElem(SqList L, ELemType e/* , Status compare() */) {
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            return i+1;
        }
    }
    return ERROR;
}

//若cur_e是L的元素，用pre_e返回cur_e的前驱。
Status PriorElem(SqList L, ELemType cur_e, const ELemType* pre_e) {
    return OK;
}

//若cur_e是L的元素，用nxt_e返回cur_e的前驱。
Status NextElem(SqList L, ELemType cur_e, const ELemType* nxt_e) {
    return OK;
}

//~在顺序线性表L中第index个位置插入新的元素e。
Status ListInsert(p_SqList L, int index, ELemType e) {
    //i的合法值为 1 <= i <= ListLength(L)+1 。
    if(index < 1 || index > L->length + 1) return ERROR; /* 1.考虑插入的位置是否合法，即是否在区间[1, size + 1]中 */
    if(L->length == L->listsize) {
        /* 2.考虑表满了，length已经达到了capacity的大小,要扩容。。。 */
        int new_listsize = L->listsize + LIST_INCREMENT; //在原有初始分配量上加上LIST_INCREMENT
        ELemType* new_e = realloc(L->elem, sizeof(ELemType)); //这里我们使用新的函数realloc()重新申请更大的内存空间
        if(new_e == NULL) return ERROR; /* 3.考虑若内存挤爆，申请失败，只能返回0表示插入失败了 */
        L->listsize = new_listsize;
        L->elem = new_e;
    }
    for (int i = L->length; i >= index; i--) {
        L->elem[i] = L->elem[i-1]; //数组下表从0开始数,length/index从1开始算，正好构成了elem[L->length - 1]是最后一个元素，而elem[L->length]是最后一个元素后的那个空位。
    }
    L->elem[index - 1] = e; //数组下表从0开始数,length/index从1开始算，正好。。。
    L->length++;
    return OK;
}

//~删除L的第i个元素，并用e返回其值，L的长度减1。
Status ListDelete(p_SqList L, int index, const ELemType* e) { //0.0
    if(index < 1 || index > L->length) return 0;
    e = &(L->elem[index-1]); //0.0
    printf("the be deleted elem is %d.\n", *e); //0.0
    for (int i = index - 1; i < L->length; i++) {
        L->elem[i] = L->elem[i + 1]; //数组下表从0开始数,length/index从1开始算，正好。。。
    }
    L->length--;
    return OK;
}

//~依此对L的每个数据元素调用函数visit()。
Status ListTraverse(p_SqList L/* , visit() */){
    for (int i = 0; i < L->length; i++)
        printf("%d ", L->elem[i]);
    printf("\n");
    return OK;
}

//p21
void MergeList(SqList la, SqList Lb, p_SqList Lc) {
    ;
}

int main() {
    printf("------------------------------\n");

    SqList L;
    InitList(&L);
    printf("%d %d\n", L.length, L.listsize);
    ListInsert(&L, 1, 666);
    ListInsert(&L, 1, 777);
    ListInsert(&L, 2, 888);
    ListInsert(&L, 1, 999);
    ListInsert(&L, 3, 111);
    ListTraverse(&L);
    ELemType the_e; //0.0
    ListDelete(&L, 2, &the_e); //0.0
    ListTraverse(&L);
    printf("ListLength(&L) is %d.\n", ListLength(&L));
    printf("elem in index=3 is %d.\n", GetElem(L, 3, &the_e));
    printf("index in elem=111 is %d\n", LocateElem(L, 111));

    printf("------------------------------\n");
}

/*
 * 关于克服C++引用类型的影响：
 *
 * 书上函数参数有&时(本质表示的是地址型，所以)，你也传一个地址型。书上直接传的是内容型那你也传内容型。
 * 调用这个函数时，传带&的(将内容型转换成地址型); 如果之前没有这个变量就新建这个变量，因为要传加&的，所以新建的是内容型。
 * 关键是清楚的知道你需要的是地址型还是内容型。
 *
 * chat_gpt:这个警告出现在你的代码中当一个函数接受一个指针作为参数，并且这个函数不会修改指针所指向的对象时。在这种情况下，最好使用指向常量的指针（const T*），而不是普通指针（T*），以明确表明函数不会修改指针指向的数据。
 *
 * */
