#include<stdio.h>

int main()
{
    int a,b;
    while(scanf("%d%d",&a,&b)!=EOF)
    {
        if(a == 0 && b== 0)
        {
            break;
        }
        else
        {
            int sum=a+b;
            printf("%d\n",sum);
        }
    }
    return 0;
}

/*
问题 D: 22-循环-1-输入输出练习3
[命题人 : admin]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
输入两个数，输出他们的和。
输入
多样例输入，每行两个数字a,b，均在int范围内
当a和b同时为0时，跳出循环，本样例不做处理
输出
输出a+b的值，其值在int范围内，每个结果占一行 
样例输入 Copy
10 10
20 20
25 25
0 0
样例输出 Copy
20
40
50
*/