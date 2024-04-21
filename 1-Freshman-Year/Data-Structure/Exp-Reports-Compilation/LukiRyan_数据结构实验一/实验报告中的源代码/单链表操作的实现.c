#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct Node {
    int data; // 数据域
    struct Node *next; // 指针域，指向下一个节点
} Node, *LinkedList;

// 菜单函数
void Menu() {
    printf("\n");
    printf("1->>创建链表\n");
    printf("2->>插入元素\n");
    printf("3->>删除元素\n");
    printf("4->>查找元素\n");
    printf("5->>显示链表\n");
    printf("0->>退出程序\n");
    printf("\n");
}

// 创建链表函数
LinkedList Create_List() {
    int n, i, x;
    LinkedList head, p, q;
    head = (LinkedList)malloc(sizeof(Node)); // 创建头结点
    head->next = NULL;
    printf("请输入要创建的链表中元素的个数：");
    scanf("%d", &n);
    q = head; // 初始化尾节点
    for (i = 1; i <= n; i++) {
        printf("请输入第 %d 个元素的值：", i);
        scanf("%d", &x);
        p = (LinkedList)malloc(sizeof(Node)); // 创建新节点
        p->data = x; // 将数据存入新节点
        q->next = p; // 将新节点插入链表末尾
        q = p; // 更新尾节点
    }
    q->next = NULL; // 将链表末尾的节点的 next 指针置为 NULL
    return head; // 返回头结点
}

// 插入元素函数
void Insert(LinkedList head) {
    int x;
    LinkedList p = (LinkedList)malloc(sizeof(Node)); // 创建新节点
    printf("请输入要插入的元素的值：");
    scanf("%d", &x);
    p->data = x; // 将数据存入新节点
    p->next = head->next; // 将新节点插入链表头部
    head->next = p; // 更新头结点的 next 指针
    printf("元素 %d 已插入链表头部。\n", x);
}

// 删除元素函数
void Delete(LinkedList head) {
    int x, pos;
    printf("请输入要删除的元素的值：");
    scanf("%d", &x);
    pos = Find(head, x); // 调用 Find 函数查找元素位置
    if (pos == -1) {
        printf("未找到元素 %d！\n", x);
    } else {
        LinkedList p = head;
        for (int i = 1; i < pos; i++) {
            p = p->next; // 移动指针到要删除的元素的前一个位置
        }
        LinkedList q = p->next; // q 指向要删除的元素
        p->next = q->next; // 删除 q 指向的元素
        free(q); // 释放 q 所占的内存
        printf("元素 %d 已从链表中删除。\n", x);
    }
}

// 查找元素
int Find(LinkedList head, int x) {
    int pos = 1;
    LinkedList p = head->next;
    while (p != NULL) {
        if (p->data == x) {
            return pos; // 找到元素，返回位置
        }
        pos++;
        p = p->next; // 移动指针
    }
    return -1; // 没有找到元素，返回 -1
}

// 显示链表函数
void Show_List(LinkedList head) {
    if (head->next == NULL) {
        printf("链表为空！\n");
    } else {
        LinkedList p = head->next;
        printf("链表中的元素为：");
        while (p != NULL) {
            printf("%d ", p->data);
            p = p->next; // 移动指针
        }
        printf("\n");
    }
}

// 主函数
int main() {
    int choice;
    LinkedList head = NULL;
    while (1) {
        Menu(); // 显示菜单
        printf("请输入您的选择：");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                head = Create_List(); // 创建链表
                break;
            case 2:
                if (head == NULL) {
                    printf("请先创建链表！\n");
                } else {
                    Insert(head); // 插入元素
                }
                break;
            case 3:
                if (head == NULL) {
                    printf("请先创建链表！\n");
                } else {
                    Delete(head); // 删除元素
                }
                break;
            case 4: {
                int x, pos;
                printf("请输入要查找的元素的值：");
                scanf("%d", &x);
                pos = Find(head, x); // 查找元素位置
                if (pos == -1) {
                    printf("未找到元素 %d！\n", x);
                } else {
                    printf("元素 %d 在链表中的位置为 %d。\n", x, pos);
                }
                break;
            }
            case 5:
                if (head == NULL) {
                    printf("请先创建链表！\n");
                } else {
                    Show_List(head); // 显示链表
                }
                break;
            case 0:
                printf("程序已退出。\n");
                return 0;
            default:
                printf("输入有误，请重新输入！\n");
                break;
        }
    }
}