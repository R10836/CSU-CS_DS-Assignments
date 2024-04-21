#include <stdio.h>

struct Person {
    char name[50];
    int age;
    float height;
};

int main() {
    struct Person person1;
    struct Person* ptrPerson = &person1;

    // 使用"."运算符访问结构体成员
    person1.age = 30;

    // 使用"->"运算符访问结构体成员
    ptrPerson->age = 30;

    printf("Age using '.' operator: %d\n", person1.age);
    printf("Age using '->' operator: %d\n", ptrPerson->age);

    return 0;
}
