//
// Created by 33712 on 2023/7/29.
//
//------------------stack--------------------



#include <stdio.h>
#include <stdlib.h>



#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE (-1)
#define OVERFLOW (-2)
#define STACK_INIT_SIZE 100 //存储空间的初始分配量
#define STACK_INCREMENT 10 //储空间的分配增量



typedef int Status; //Status是函数的类型，其值是函数结果状态代码
typedef int ELemType; //ELemType是表里元素的类型
typedef struct Stack{
    ELemType* base; //在栈构造前和销毁后，base值为NULL //存储空间基址
    ELemType* top; //栈顶指针
    int stacksize; //当前已分配的存储空间，以元素为单位
} * p_SqStack;
//等价于
//typedef struct Stack SqStack;
//typedef struct Stack* p_SqStack;



//~《创》构造一个空栈S。
Status InitStack(p_SqStack S) {
    S->base = (ELemType*) malloc(STACK_INIT_SIZE * sizeof(ELemType));
    if(S->base == NULL) return ERROR;
    S->top = S->base; //栈顶指针=栈底指针
    S->stacksize = STACK_INIT_SIZE; //存储空间大小=初始分配量
    return OK;
}

//《销》栈S被销毁。
Status DestroyStack() {
    return OK;
}

//将S清为空栈。
Status ClearStack() {
    return OK;
}

//~若栈S为空栈，则返回TRUE，否则FALSE。
Status StackEmpty(p_SqStack S) {
    //判空
    if (S->top == S->base) return TRUE;
    else return FALSE;
}

//~返回S的元素个数，即栈的长度。
int StackLength(p_SqStack S) {
    if (S->top == S->base) return ERROR;
    return (S->top - S->base);
}

//~《查》用e返回S的栈顶元素。
ELemType GetTop(p_SqStack S) {
    if (S->top == S->base) return ERROR;
    return *(S->top - 1);
}

//~《增》插入元素e为新的栈顶元素。
Status Push(p_SqStack S, ELemType e) {
    if (S->top - S->base >= S->stacksize) { //若栈满，追加存储空间
        S->base = (ELemType*) realloc(S->base, (S->stacksize + STACK_INCREMENT) * sizeof(ELemType));
        if (S->base == NULL) return ERROR;
        S->top = S->base + S->stacksize;
        S->stacksize += STACK_INCREMENT;
    }
    *(S->top) = e; //先给当前地址上的内容赋值e
    S->top++; //再++上移一位
    //现在top指向的是顶端元素的地址（无内容，因为上移了）；base指向的是最底部元素的地址（有内容）。
    return OK;
}

//~《删》删除S的栈顶元素，并用e返回其值。
ELemType Pop(p_SqStack S) {
    if (S->top == S->base) return ERROR; //栈空，报错
    ELemType e = *(S->top - 1); //自改：切莫忘了-1！以及为什么-1！
    S->top--;
    return e;
}

//~从栈底到栈顶依次对S的每个数据元素调用函数visit()。一旦visit()失败，则操作失效。
Status StackTraverse(p_SqStack S) {
    for (int i = 0; S->base[i] != *(S->top); i++) { //循环条件自改了
        printf("%d ", S->base[i]);
    }
    printf("\n");
    return OK;
}

//------------------------------------自加

int main() {
    printf("------------------------------\n");

    struct Stack S;
    InitStack(&S);
    printf("1 means empty, 0 means not empty, so the stack now is %d.\n", StackEmpty(&S));
    Push(&S, 111);
    Push(&S, 222);
    Push(&S, 333);
    Push(&S, 444);
    Push(&S, 555);
    StackTraverse(&S);
    printf("use StackLength(), stack's $used$ length is %d.\n", StackLength(&S));
    printf("now, base is %d.\n", *(S.base));
    printf("now, top is %d.\n", *(S.top - 1));
    printf("use Pop(&S), the deleted elem is %d.\n", Pop(&S));
    StackTraverse(&S);
    printf("use Pop(&S), the deleted elem is %d.\n", Pop(&S));;
    StackTraverse(&S);
    printf("now use GetTop(), top is %d.\n", GetTop(&S));
    printf("use StackLength(), stack's $used$ length is %d.\n", StackLength(&S));
    printf("1 means empty, 0 means not empty, so the stack now is %d.\n", StackEmpty(&S));

    printf("------------------------------\n");
}