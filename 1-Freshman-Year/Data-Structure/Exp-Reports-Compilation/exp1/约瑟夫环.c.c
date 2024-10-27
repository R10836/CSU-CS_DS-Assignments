#include <stdio.h>
#include <stdlib.h>

typedef int Status;
typedef struct node {
    int num;             // ���˵ı��
    int data;            // ���˵�����
    struct node* next;
} Node, * LNode;         // ��������ڵ㼰ָ������

// ����һ����n���˵�ѭ��������ģ����й���
Status Josephus(LNode* L, int n) {
    *L = (LNode)malloc(sizeof(Node));     // ����ͷ�ڵ�
    (*L)->next = NULL;
    LNode p = *L;                         // pָ��ǰ����ĩβ
    for (int i = 0; i < n; i++) {
        LNode a = (LNode)malloc(sizeof(Node));  // �����½ڵ�
        printf("�� %d ���˵����룺", i + 1);
        scanf("%d", &a->data);
        p->next = a;                   // ���½ڵ���뵽����ĩβ
        p = p->next;
        p->num = i + 1;                // ���ø��˵ı��
    }
    p->next = (*L)->next;              // ��������β����
    return 0;
}

// ��ѭ��������ģ�ⱨ�����й���
Status MoveOut(LNode* L, int i, int* m) {
    LNode p = *L;                      // pָ��ǰ�ڵ�
    int j = 0;
    for (; j < i - 1; j++) {
        p = p->next;                  // �ҵ���i-1���ڵ�
    }
    *m = p->next->data;                // ��ȡ��i���ڵ������
    LNode a = p->next;                 // aָ���i���ڵ�
    printf("%d ", p->next->num);       // �����i���˵ı��
    p->next = a->next;                 // ɾ����i���ڵ�
    *L = p;
    free(a);                           // �ͷŵ�i���ڵ���ڴ�
    return 0;
}

int main() {
    LNode L;
    int n, m;
    printf("���������� n��");
    scanf("%d", &n);
    Josephus(&L, n);
    printf("�������ʼ��������ֵ m��");
    scanf("%d", &m);
    printf("\n����˳��");
    for (int i = n; i > 0; i--) {
        MoveOut(&L, m % i, &m);   // ģ�ⱨ������
    }
    return 0;
}