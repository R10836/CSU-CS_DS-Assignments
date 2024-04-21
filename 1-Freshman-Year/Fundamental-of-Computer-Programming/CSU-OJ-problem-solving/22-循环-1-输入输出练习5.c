#include<stdio.h>


int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        int m;
        for(int i=0; i<n; i++)
        {
            scanf("%d",&m);
            int x, sum=0;
            for (int i=0; i<m; i++)
            {
                scanf("%d",&x);
                sum+=x;
            }
            printf("%d\n\n",sum);
        }
    }
    return 0;
}

/*
问题 E: 22-循环-1-输入输出练习5
[命题人 : admin]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
你的任务是计算多个数的和。
输入
第一行输入一个整数 n。接下来的 n行，每行都以一个整数m开头，接下来的m个数位于同一行。数据均在int范围内。
输出
对于输入的每组数据，你需要在一行内输出它们的和（同样的第一个数字m不算），且需要注意的是每组输出之间都要有一个空行。
样例输入 Copy
3
4 1 2 3 4
5 1 2 3 4 5
3 1 2 3
样例输出 Copy
10

15

6
*/