#include <stdio.h>

typedef struct Student {
    int id;
    int age;
    char *name;
} Stu, s, t, u;

int main() {
    Stu student1; // 声明一个 struct Student 类型的变量，使用 Stu 作为数据类型别名
    s student2;   // 声明一个 struct Student 类型的变量，使用 s 作为数据类型别名
    t student3;   // 声明一个 struct Student 类型的变量，使用 t 作为数据类型别名
    u student4;   // 声明一个 struct Student 类型的变量，使用 u 作为数据类型别名
    student3.age=1;
    printf("%d", student3.age)
}