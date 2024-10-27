#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef struct node {
    int num;             // 该人的编号
    int data;            // 该人的密码
    struct node* next;
} Node, * LNode;         // 定义链表节点及指针类型

// 建立一个有n个人的循环链表，并模拟出列过程
Status Josephus(LNode* L, int n) {
    *L = (LNode)malloc(sizeof(Node));     // 分配头节点
    (*L)->next = NULL;
    LNode p = *L;                         // p指向当前链表末尾
    for (int i = 0; i < n; i++) {
        LNode a = (LNode)malloc(sizeof(Node));  // 创建新节点
        printf("第 %d 个人的密码：", i + 1);
        scanf("%d", &a->data);
        p->next = a;                   // 将新节点插入到链表末尾
        p = p->next;
        p->num = i + 1;                // 设置该人的编号
    }
    p->next = (*L)->next;              // 将链表首尾相连
    return 0;
}

// 在循环链表中模拟报数出列过程
Status MoveOut(LNode* L, int i, int* m) {
    LNode p = *L;                      // p指向当前节点
    int j = 0;
    for (; j < i - 1; j++) {
        p = p->next;                  // 找到第i-1个节点
    }
    *m = p->next->data;                // 获取第i个节点的密码
    LNode a = p->next;                 // a指向第i个节点
    printf("%d ", p->next->num);       // 输出第i个人的编号
    p->next = a->next;                 // 删除第i个节点
    *L = p;
    free(a);                           // 释放第i个节点的内存
    return 0;
}

int main() {
    LNode L;
    int n, m;
    printf("请输入人数 n：");
    scanf("%d", &n);
    Josephus(&L, n);
    printf("请输入初始报数上限值 m：");
    scanf("%d", &m);
    printf("\n出列顺序：");
    for (int i = n; i > 0; i--) {
        MoveOut(&L, m % i, &m);   // 模拟报数出列
    }
    return 0;
}