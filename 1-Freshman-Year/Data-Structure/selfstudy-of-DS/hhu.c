#include <stdlib.h>
#include <stdio.h>



//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE (-1)
#define OVERFLOW (-2)
#define LIST_INIT_SIZE 100
#define LIST_INCREMENT 10



typedef int Status; //Status是函数的类型，其值是函数结果状态代码
typedef int ELemType; //ELemType是表里元素的类型
struct List {
    ELemType* elem; //存储空间基址
    int length; //当前长度
    int listsize; //当前分配的存储容量(以一个sizeof(ElemType)为单位)
};
typedef struct List SqList;
typedef struct List* p_SqList; //替代c++的引用。。。现在代表了指向struct List结构体的指针类型。



_Bool initList(p_SqList list) {
    //构造一个空的线性表L。（就是给ArrayList的实例list的各个元素赋值）
    list->elem = malloc(sizeof(ELemType) * LIST_INIT_SIZE); //malloc返回的是指向这一片存储空间开始地点的指针；所以arr这个ele*型的变量 为 指向malloc申请出来空间的开始地点的指针。
    if(list->elem == NULL) return ERROR;  //需要判断:如果申请的结果为NULL的话表示内存空间申请失败
    list->listsize = LIST_INIT_SIZE;
    list->length = 0;
    return OK; //正常情况下返回true也就是1
}

//插入操作
_Bool insertList(p_SqList list, ELemType new_element, int index) {
    //list就是待操作的表，new_data就是需要插入的元素，index就是插入的位置（注意顺序表的index是按位序计算的，从1开始，一般都是第index个元素）
    //1.考虑插入的位置是否合法，即是否在区间[1, size + 1]中
    if(index < 1 || index > list->length + 1) return 0;
    //2.考虑表满了，length已经达到了capacity的大小,要扩容。。。
    if(list->length == list->listsize) {
        int new_capacity = list->listsize + LIST_INCREMENT; //在原有MaxSize上加上PlusSize
        ELemType* new_data = realloc(list->elem, sizeof(ELemType));  //这里我们使用新的函数realloc()重新申请更大的内存空间
        if(new_data == NULL) return 0; //如果申请失败，那么就确实没办法插入了，只能返回0表示插入失败了
        list->listsize = new_capacity;
        list->elem = new_data;
    }
    for (int i = list->length; i >= index; i--) {
        list->elem[i] = list->elem[i-1]; //数组下表从0开始数，length从1开始算，正好构成了data[list->length - 1]是最后一个元素，而data[list->length]是最后一个元素后的那个空位。
    }
    list->elem[index - 1] = new_element; //数组下表从0开始数,length/index从1开始算，正好。。。
    list->length++;
    return 1;
}

//删除操作
_Bool deleteList(p_SqList list, int index) {
    if(index < 1 || index > list->length) return 0;
    for (int i = index - 1; i < list->length; i++) {
        list->elem[i] = list->elem[i + 1]; //数组下表从0开始数,length/index从1开始算，正好。。。
    }
    list->length--;
    return 1;
}

//获取长度
int getLength(p_SqList list) {
    return list->length;
}

//由位置得元素
ELemType* pos_2_get_ele(p_SqList list, int index) {
    if(index < 1 || index > list->length) return NULL;   //如果超出范围就返回NULL
    return &list->elem[index - 1];
}

//由元素得位置
int ele_2_get_pos(p_SqList list, ELemType element) {
    for (int i = 0; i < list->length; i++) {   //一直遍历，如果找到那就返回位序
        if(list->elem[i] == element) return i + 1;
    }
    return -1;  //如果遍历完了都没找到，那么就返回-1
}

//打印顺序表
void printList(p_SqList list){   //编写一个函数用于打印表当前的数据
    for (int i = 0; i < list->length; i++)   //表里面每个元素都拿出来打印一次
        printf("%d ", list->elem[i]);
    printf("\n");
}

int main() {
    struct List list;
    if(initList(&list) == 1) {
        insertList(&list, 666, 1);
        printList(&list);
        insertList(&list, 777, 1);
        printList(&list);
        insertList(&list, 888, 2);
        printList(&list);
        if(insertList(&list, 222, 10086)) {
            printList(&list);
        } else {
            printf("shut fail插入失败！\n");
        }
        for (int i = 0; i < 30; ++i) {
            insertList(&list, i, i);
        }
        printList(&list);
        deleteList(&list, 5);   //这里删除5号元素
        printList(&list);
    } else {
        printf("init fail顺序表初始化失败，无法启动程序！\n");
    }
}

//原作完整代码：
//#include <stdio.h>
//#include <stdlib.h>
//
//typedef int E;
//
//struct List {
//    E * array;
//    int listsize;
//    int size;
//};
//
//typedef struct List * p_SqList;
//
//_Bool initList(p_SqList list){
//    list->array = malloc(sizeof(E) * 10);
//    if(list->array == NULL) return 0;
//    list->listsize = 10;
//    list->size = 0;
//    return 1;
//}
//
//_Bool insertList(p_SqList list, E element, int index){
//    if(index < 1 || index > list->size + 1) return 0;
//
//    if(list->size == list->listsize) {
//        int newCapacity = list->listsize + (list->listsize >> 1);
//        E * newArray = realloc(list->array, newCapacity * sizeof(E));
//        if(newArray == NULL) return 0;
//        list->array = newArray;
//        list->listsize = newCapacity;
//    }
//
//    for (int i = list->size; i > index - 1; --i)
//        list->array[i] = list->array[i - 1];
//    list->array[index - 1] = element;
//    list->size++;
//    return 1;
//}
//
//_Bool deleteList(p_SqList list, int index){
//    if(index < 1 || index > list->size) return 0;
//    for (int i = index - 1; i < list->size - 1; ++i)
//        list->array[i] = list->array[i + 1];
//    list->size--;
//    return 1;
//}
//
//int sizeList(p_SqList list){
//    return list->size;
//}
//
//E * getList(p_SqList list, int index){
//    if(index < 1 || index > list->size) return NULL;
//    return &list->array[index - 1];
//}
//
//int findList(p_SqList list, E element){
//    for (int i = 0; i < list->size; ++i) {
//        if(list->array[i] == element) return i + 1;
//    }
//    return -1;
//}