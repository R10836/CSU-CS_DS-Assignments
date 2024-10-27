#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME_LEN 20 // ������������

// ����һ�����нṹ��
typedef struct City {
    char name[MAX_NAME_LEN]; // ������
    double x; // ������
    double y; // ������
    struct City* next; // ָ����һ�����е�ָ��
} City;

// ����ȫ�ֱ�������ʾ�����ͷ���
City* head;

// ��������
void Menu();
void Insert();
void Delete();
void Update();
void GetSiteByName();
void GetNameBySite();
void CityList();

int main() {
    head = (City*)malloc(sizeof(City)); // ����ͷ���Ŀռ�
    head->next = NULL; // ͷ����ָ�����ʼ��Ϊ NULL
    while (1) {
        Menu(); // ��ʾ�˵�
        int choice;
        printf("����������ѡ��");
        scanf("%d", &choice);
        switch (choice) {
            case 1: 
                Insert(); // ���������Ϣ
                break;
            case 2: 
                Delete(); // ɾ��������Ϣ
                break;
            case 3: 
                Update(); // ���³�����Ϣ
                break;
            case 4: 
                GetSiteByName(); // ���ݳ��������ҳ�������
                break;
            case 5: 
                GetNameBySite(); // ���ݳ���������ҳ�����
                break;
            case 6: 
                CityList(); // չʾ���������г�����Ϣ
                break;
            case 0: 
                exit(0); // �˳�����
            default: 
                printf("����������������룡\n"); // ���������������
        }
    }
    return 0;
}

// ��ʾ�˵�����
void Menu() {
    printf("=================������Ϣ����ϵͳ=================\n");
    printf("1. ���������Ϣ\n");
    printf("2. ɾ��������Ϣ\n");
    printf("3. ���³�����Ϣ\n");
    printf("4. �ɳ��в�����\n");
    printf("5. ����������\n");
    printf("6. չʾ���������Ϣ\n");
    printf("0. �˳�����\n");
}

// ������к���
void Insert() {
    char name[MAX_NAME_LEN];  // ����һ���ַ��������洢������
    double x, y;  // ��������double���͵ı����洢��������

    printf("������������������ꡢ�����꣺");
    scanf("%s %lf %lf", name, &x, &y);  // ���û������ж��������������

    // �ж������Ƿ�Ϊ�գ����Ϊ�գ����½ڵ�ֱ�Ӳ��뵽ͷ���֮��
    if (head->next == NULL) {
        City* newCity = (City*)malloc(sizeof(City));  // �����½ڵ�ռ�
        strcpy(newCity->name, name);  // �������������½ڵ���
        newCity->x = x;  // ������������½ڵ���
        newCity->y = y;  // ������������½ڵ���
        newCity->next = NULL;  // ���½ڵ��ָ�����ʼ��ΪNULL
        head->next = newCity;  // ��ͷ����ָ����ָ���½ڵ�
        printf("����ɹ���\n");
        return;
    }
    // ���������ҵ�����λ�ã�Ҫ�������ճ������ֵ�����������
    City* p = head;
    while (p->next != NULL && strcmp(p->next->name, name) < 0) {
        p = p->next;
    }
    // �ж��Ƿ��ҵ��Ѵ��ڵĳ�����������ҵ�������ʧ��
    if (p->next != NULL && strcmp(p->next->name, name) == 0) {
        printf("�������Ѵ��ڣ�����ʧ�ܣ�\n");
        return;
    }
    // �����½ڵ�
    City* newCity = (City*)malloc(sizeof(City));  // �����½ڵ�ռ�
    strcpy(newCity->name, name);  // �������������½ڵ���
    newCity->x = x;  // ������������½ڵ���
    newCity->y = y;  // ������������½ڵ���
    newCity->next = p->next;  // ���½ڵ���뵽p�ĺ���
    p->next = newCity;  // ��p��ָ����ָ���½ڵ�
    printf("����ɹ���\n");
}

// ɾ�����к���
void Delete() {
    char name[MAX_NAME_LEN];
    printf("������Ҫɾ���ĳ�������");
    scanf("%s", name);
    City* p = head; // ����һ��ָ��ͷ����ָ��p
    while (p->next != NULL && strcmp(p->next->name, name) != 0) { // ���������ҵ�Ҫɾ���ĳ��н��λ��
        p = p->next;
    }

    if (p->next == NULL) { // �ж��Ƿ��ҵ�Ҫɾ���ĳ��н��
        printf("���в����ڣ�ɾ��ʧ�ܣ�\n");
        return;
    }

    City* temp = p->next; // ����һ����ʱָ�룬ָ��Ҫɾ���ĳ��н��
    p->next = p->next->next; // ɾ��Ҫɾ���ĳ��н��
    free(temp); // �ͷ�Ҫɾ���ĳ��н����ڴ�ռ�
    printf("ɾ���ɹ���\n");
}

// ���³��к���
void Update() {
    char name[MAX_NAME_LEN];  // ����һ���ַ�����洢������
    double x, y;  // ���������������洢������Ϣ
    printf("������Ҫ���µĳ������������ꡢ�����꣺");
    scanf("%s %lf %lf", name, &x, &y);  // ��ȡ�û�����ĳ��������������������
    City* p = head->next;  // ������ͷ����һ���ڵ㿪ʼ����
    while (p != NULL && strcmp(p->name, name) != 0) {  // ���p��Ϊ����p��name�������name����ȣ��ͼ�������
        p = p->next;
    }
    if (p == NULL) {  // �������������pΪ�գ���˵��������û�иó��У�����ʧ��
        printf("���в����ڣ�����ʧ�ܣ�\n");
        return;
    }
    p->x = x;  // ���ó��еĺ��������Ϊ�û�����ĺ�����
    p->y = y;  // ���ó��е����������Ϊ�û������������
    printf("���³ɹ���\n");  // ������³ɹ�����ʾ��Ϣ
}

// �ɳ��в����꺯��
void GetSiteByName() {
    char name[MAX_NAME_LEN];
    printf("������Ҫ���ҵĳ�������");
    scanf("%s", name);
    // ����������ҳ���
    City* p = head->next;
    while (p != NULL && strcmp(p->name, name) != 0) {
        p = p->next;
    }
    // �ж��Ƿ���ҳɹ�
    if (p == NULL) {
        printf("���в����ڣ�\n");
        return;
    }
    // �������������Ϣ
    printf("%s������Ϊ��(%.2lf, %.2lf)\n", name, p->x, p->y);
}

// ���������к���
void GetNameBySite() {
    double x, y, d;  // ����Ҫ���ҵĺ����ꡢ������;���
    printf("������Ҫ���ҵĺ����ꡢ�����ꡢ���룺");
    scanf("%lf %lf %lf", &x, &y, &d);  // ����Ҫ���ҵĺ����ꡢ������;���
    int count = 0;  // �������Ҫ��ĳ��м�����
    City* p = head->next;  // ������ͷ�ڵ����һ���ڵ㿪ʼ����
    while (p != NULL) {  // ��������
        double dist = sqrt((p->x - x) * (p->x - x) + (p->y - y) * (p->y - y));  // ���㵱ǰ�ڵ������Ҫ���ҵ�����ľ���
        if (dist <= d) {  // �������С�ڵ���Ҫ���ҵľ���
            printf("%s������Ϊ��(%.2lf, %.2lf)\n", p->name, p->x, p->y);  // �����ǰ���е�����
            count++;  // ��������1
        }
        p = p->next;  // ����������һ���ڵ�
    }
    if (count == 0) {  // ���û���ҵ�����Ҫ��ĳ���
        printf("û���ҵ���ָ���������С�ڵ���%.2lf�ĳ��У�\n", d);
    }
}

// ��ʾ���������еĳ���
void CityList() {
    // �������Ϊ�գ��������ʾ��Ϣ������
    if (head->next == NULL) {
        printf("����Ϊ�գ�\n");
        return;
    }
    // ������������г��е����Ƽ�����
    printf("���������еĳ���Ϊ��\n");
    City* p = head->next;  // ������ĵ�һ���ڵ㿪ʼ����
    while (p != NULL) {
        printf("%s:(%.2lf, %.2lf)\n", p->name, p->x, p->y);  // ����������Ƽ�������
        p = p->next;  // ָ����һ���ڵ�
    }
}