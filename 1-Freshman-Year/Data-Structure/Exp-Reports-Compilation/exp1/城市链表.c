#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME_LEN 20 // 最大城市名长度

// 定义一个城市结构体
typedef struct City {
    char name[MAX_NAME_LEN]; // 城市名
    double x; // 横坐标
    double y; // 纵坐标
    struct City* next; // 指向下一个城市的指针
} City;

// 定义全局变量，表示链表的头结点
City* head;

// 声明函数
void Menu();
void Insert();
void Delete();
void Update();
void GetSiteByName();
void GetNameBySite();
void CityList();

int main() {
    head = (City*)malloc(sizeof(City)); // 分配头结点的空间
    head->next = NULL; // 头结点的指针域初始化为 NULL
    while (1) {
        Menu(); // 显示菜单
        int choice;
        printf("请输入您的选择：");
        scanf("%d", &choice);
        switch (choice) {
            case 1: 
                Insert(); // 插入城市信息
                break;
            case 2: 
                Delete(); // 删除城市信息
                break;
            case 3: 
                Update(); // 更新城市信息
                break;
            case 4: 
                GetSiteByName(); // 根据城市名查找城市坐标
                break;
            case 5: 
                GetNameBySite(); // 根据城市坐标查找城市名
                break;
            case 6: 
                CityList(); // 展示链表中所有城市信息
                break;
            case 0: 
                exit(0); // 退出程序
            default: 
                printf("输入错误，请重新输入！\n"); // 输入错误，重新输入
        }
    }
    return 0;
}

// 显示菜单函数
void Menu() {
    printf("=================城市信息管理系统=================\n");
    printf("1. 插入城市信息\n");
    printf("2. 删除城市信息\n");
    printf("3. 更新城市信息\n");
    printf("4. 由城市查坐标\n");
    printf("5. 由坐标查城市\n");
    printf("6. 展示链表城市信息\n");
    printf("0. 退出程序\n");
}

// 插入城市函数
void Insert() {
    char name[MAX_NAME_LEN];  // 声明一个字符串变量存储城市名
    double x, y;  // 声明两个double类型的变量存储横纵坐标

    printf("请输入城市名、横坐标、纵坐标：");
    scanf("%s %lf %lf", name, &x, &y);  // 从用户输入中读入城市名和坐标

    // 判断链表是否为空，如果为空，将新节点直接插入到头结点之后
    if (head->next == NULL) {
        City* newCity = (City*)malloc(sizeof(City));  // 分配新节点空间
        strcpy(newCity->name, name);  // 将城市名存入新节点中
        newCity->x = x;  // 将横坐标存入新节点中
        newCity->y = y;  // 将纵坐标存入新节点中
        newCity->next = NULL;  // 将新节点的指针域初始化为NULL
        head->next = newCity;  // 将头结点的指针域指向新节点
        printf("插入成功！\n");
        return;
    }
    // 遍历链表找到插入位置，要求链表按照城市名字典序升序排序
    City* p = head;
    while (p->next != NULL && strcmp(p->next->name, name) < 0) {
        p = p->next;
    }
    // 判断是否找到已存在的城市名，如果找到，插入失败
    if (p->next != NULL && strcmp(p->next->name, name) == 0) {
        printf("城市名已存在，插入失败！\n");
        return;
    }
    // 创建新节点
    City* newCity = (City*)malloc(sizeof(City));  // 分配新节点空间
    strcpy(newCity->name, name);  // 将城市名存入新节点中
    newCity->x = x;  // 将横坐标存入新节点中
    newCity->y = y;  // 将纵坐标存入新节点中
    newCity->next = p->next;  // 将新节点插入到p的后面
    p->next = newCity;  // 将p的指针域指向新节点
    printf("插入成功！\n");
}

// 删除城市函数
void Delete() {
    char name[MAX_NAME_LEN];
    printf("请输入要删除的城市名：");
    scanf("%s", name);
    City* p = head; // 定义一个指向头结点的指针p
    while (p->next != NULL && strcmp(p->next->name, name) != 0) { // 遍历链表，找到要删除的城市结点位置
        p = p->next;
    }

    if (p->next == NULL) { // 判断是否找到要删除的城市结点
        printf("城市不存在，删除失败！\n");
        return;
    }

    City* temp = p->next; // 定义一个临时指针，指向要删除的城市结点
    p->next = p->next->next; // 删除要删除的城市结点
    free(temp); // 释放要删除的城市结点的内存空间
    printf("删除成功！\n");
}

// 更新城市函数
void Update() {
    char name[MAX_NAME_LEN];  // 声明一个字符数组存储城市名
    double x, y;  // 声明两个浮点数存储坐标信息
    printf("请输入要更新的城市名、横坐标、纵坐标：");
    scanf("%s %lf %lf", name, &x, &y);  // 读取用户输入的城市名、横坐标和纵坐标
    City* p = head->next;  // 从链表头的下一个节点开始遍历
    while (p != NULL && strcmp(p->name, name) != 0) {  // 如果p不为空且p的name和输入的name不相等，就继续遍历
        p = p->next;
    }
    if (p == NULL) {  // 如果遍历结束后p为空，则说明链表中没有该城市，更新失败
        printf("城市不存在，更新失败！\n");
        return;
    }
    p->x = x;  // 将该城市的横坐标更新为用户输入的横坐标
    p->y = y;  // 将该城市的纵坐标更新为用户输入的纵坐标
    printf("更新成功！\n");  // 输出更新成功的提示信息
}

// 由城市查坐标函数
void GetSiteByName() {
    char name[MAX_NAME_LEN];
    printf("请输入要查找的城市名：");
    scanf("%s", name);
    // 遍历链表查找城市
    City* p = head->next;
    while (p != NULL && strcmp(p->name, name) != 0) {
        p = p->next;
    }
    // 判断是否查找成功
    if (p == NULL) {
        printf("城市不存在！\n");
        return;
    }
    // 输出城市坐标信息
    printf("%s的坐标为：(%.2lf, %.2lf)\n", name, p->x, p->y);
}

// 由坐标查城市函数
void GetNameBySite() {
    double x, y, d;  // 定义要查找的横坐标、纵坐标和距离
    printf("请输入要查找的横坐标、纵坐标、距离：");
    scanf("%lf %lf %lf", &x, &y, &d);  // 输入要查找的横坐标、纵坐标和距离
    int count = 0;  // 定义符合要求的城市计数器
    City* p = head->next;  // 从链表头节点的下一个节点开始遍历
    while (p != NULL) {  // 遍历链表
        double dist = sqrt((p->x - x) * (p->x - x) + (p->y - y) * (p->y - y));  // 计算当前节点城市与要查找的坐标的距离
        if (dist <= d) {  // 如果距离小于等于要查找的距离
            printf("%s的坐标为：(%.2lf, %.2lf)\n", p->name, p->x, p->y);  // 输出当前城市的坐标
            count++;  // 计数器加1
        }
        p = p->next;  // 继续遍历下一个节点
    }
    if (count == 0) {  // 如果没有找到符合要求的城市
        printf("没有找到与指定坐标距离小于等于%.2lf的城市！\n", d);
    }
}

// 显示链表里所有的城市
void CityList() {
    // 如果链表为空，则输出提示信息并返回
    if (head->next == NULL) {
        printf("链表为空！\n");
        return;
    }
    // 输出链表中所有城市的名称及坐标
    printf("链表中所有的城市为：\n");
    City* p = head->next;  // 从链表的第一个节点开始遍历
    while (p != NULL) {
        printf("%s:(%.2lf, %.2lf)\n", p->name, p->x, p->y);  // 输出城市名称及其坐标
        p = p->next;  // 指向下一个节点
    }
}