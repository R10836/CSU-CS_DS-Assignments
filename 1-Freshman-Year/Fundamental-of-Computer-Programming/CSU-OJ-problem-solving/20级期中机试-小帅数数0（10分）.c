#include<stdio.h>

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        int num5=0;
        for(int i=1; i<=n; i++)
        {
            int i2=i;//栽在了没有另起一个变量上
            while(1)
            {
                if(i2%5!=0)
                {
                    break;
                }
                else
                {
                    num5++;
                    i2=i2/5;
                }
            }
        }
        printf("%d\n",num5);
    }
    return 0;
}

/*
问题 A: 20级期中机试-小帅数数0（10分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
小帅接到一个任务，就是要找出一个整数n！中末尾到底有多少个0，请你帮帮他。
输入
多组样例，输入一个整数n（n≤10000）
输出
对于每一个输入的n，输出一个结果。每个输出占一行。
样例输入 Copy
5
16
27
样例输出 Copy
1
3
6
*/