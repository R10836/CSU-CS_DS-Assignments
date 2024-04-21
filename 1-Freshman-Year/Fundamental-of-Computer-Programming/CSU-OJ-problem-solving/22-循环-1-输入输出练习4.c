/*
问题 E: 22-循环-1-输入输出练习4
[命题人 : admin]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
你的任务是计算若干整数的和。
输入
输入包含若干组测试数据。每组测试数据占一行，每行包含一个整数N及其后紧跟着n个整数，均在int范围内。以0开头的测试数据表示输入结束，本组数据不需要处理。
输出
对于每组输入数据，输出他们的和（注意第一个数字n是不需要算进去的），每组输出数据占用一行。
样例输入 Copy
6 1 2 3 4 5 6
8 1 2 3 4 5 6 7 8
0
样例输出 Copy
21
36
*/

#include<stdio.h>

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        if(n != 0)
        {
        int x;
        int sum=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d",&x);
            sum+=x;
        }
        printf("%d\n",sum);
        }
        else
        {
            break;
        }
    }
    return 0;
}