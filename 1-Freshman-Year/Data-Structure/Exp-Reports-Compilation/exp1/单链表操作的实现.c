#include <stdio.h>
#include <stdlib.h>

// ��������ڵ�ṹ��
typedef struct Node {
    int data; // ������
    struct Node *next; // ָ����ָ����һ���ڵ�
} Node, *LinkedList;

// �˵�����
void Menu() {
    printf("\n");
    printf("1->>��������\n");
    printf("2->>����Ԫ��\n");
    printf("3->>ɾ��Ԫ��\n");
    printf("4->>����Ԫ��\n");
    printf("5->>��ʾ����\n");
    printf("0->>�˳�����\n");
    printf("\n");
}

// ����������
LinkedList Create_List() {
    int n, i, x;
    LinkedList head, p, q;
    head = (LinkedList)malloc(sizeof(Node)); // ����ͷ���
    head->next = NULL;
    printf("������Ҫ������������Ԫ�صĸ�����");
    scanf("%d", &n);
    q = head; // ��ʼ��β�ڵ�
    for (i = 1; i <= n; i++) {
        printf("������� %d ��Ԫ�ص�ֵ��", i);
        scanf("%d", &x);
        p = (LinkedList)malloc(sizeof(Node)); // �����½ڵ�
        p->data = x; // �����ݴ����½ڵ�
        q->next = p; // ���½ڵ��������ĩβ
        q = p; // ����β�ڵ�
    }
    q->next = NULL; // ������ĩβ�Ľڵ�� next ָ����Ϊ NULL
    return head; // ����ͷ���
}

// ����Ԫ�غ���
void Insert(LinkedList head) {
    int x;
    LinkedList p = (LinkedList)malloc(sizeof(Node)); // �����½ڵ�
    printf("������Ҫ�����Ԫ�ص�ֵ��");
    scanf("%d", &x);
    p->data = x; // �����ݴ����½ڵ�
    p->next = head->next; // ���½ڵ��������ͷ��
    head->next = p; // ����ͷ���� next ָ��
    printf("Ԫ�� %d �Ѳ�������ͷ����\n", x);
}

// ɾ��Ԫ�غ���
void Delete(LinkedList head) {
    int x, pos;
    printf("������Ҫɾ����Ԫ�ص�ֵ��");
    scanf("%d", &x);
    pos = Find(head, x); // ���� Find ��������Ԫ��λ��
    if (pos == -1) {
        printf("δ�ҵ�Ԫ�� %d��\n", x);
    } else {
        LinkedList p = head;
        for (int i = 1; i < pos; i++) {
            p = p->next; // �ƶ�ָ�뵽Ҫɾ����Ԫ�ص�ǰһ��λ��
        }
        LinkedList q = p->next; // q ָ��Ҫɾ����Ԫ��
        p->next = q->next; // ɾ�� q ָ���Ԫ��
        free(q); // �ͷ� q ��ռ���ڴ�
        printf("Ԫ�� %d �Ѵ�������ɾ����\n", x);
    }
}

// ����Ԫ��
int Find(LinkedList head, int x) {
    int pos = 1;
    LinkedList p = head->next;
    while (p != NULL) {
        if (p->data == x) {
            return pos; // �ҵ�Ԫ�أ�����λ��
        }
        pos++;
        p = p->next; // �ƶ�ָ��
    }
    return -1; // û���ҵ�Ԫ�أ����� -1
}

// ��ʾ������
void Show_List(LinkedList head) {
    if (head->next == NULL) {
        printf("����Ϊ�գ�\n");
    } else {
        LinkedList p = head->next;
        printf("�����е�Ԫ��Ϊ��");
        while (p != NULL) {
            printf("%d ", p->data);
            p = p->next; // �ƶ�ָ��
        }
        printf("\n");
    }
}

// ������
int main() {
    int choice;
    LinkedList head = NULL;
    while (1) {
        Menu(); // ��ʾ�˵�
        printf("����������ѡ��");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                head = Create_List(); // ��������
                break;
            case 2:
                if (head == NULL) {
                    printf("���ȴ�������\n");
                } else {
                    Insert(head); // ����Ԫ��
                }
                break;
            case 3:
                if (head == NULL) {
                    printf("���ȴ�������\n");
                } else {
                    Delete(head); // ɾ��Ԫ��
                }
                break;
            case 4: {
                int x, pos;
                printf("������Ҫ���ҵ�Ԫ�ص�ֵ��");
                scanf("%d", &x);
                pos = Find(head, x); // ����Ԫ��λ��
                if (pos == -1) {
                    printf("δ�ҵ�Ԫ�� %d��\n", x);
                } else {
                    printf("Ԫ�� %d �������е�λ��Ϊ %d��\n", x, pos);
                }
                break;
            }
            case 5:
                if (head == NULL) {
                    printf("���ȴ�������\n");
                } else {
                    Show_List(head); // ��ʾ����
                }
                break;
            case 0:
                printf("�������˳���\n");
                return 0;
            default:
                printf("�����������������룡\n");
                break;
        }
    }
}