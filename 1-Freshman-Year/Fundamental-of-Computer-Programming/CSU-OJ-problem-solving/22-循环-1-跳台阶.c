/* 问题 J: 22-循环-1-跳台阶
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
小南在坐中南大学研发的无人车到达了目的地，从无人车下来以后，小南看到了一个长长的楼梯。
楼梯有n级台阶，小明一次可以向上跳1步，两步，甚至是n步，请问小南跳到n级台阶有多少种跳法？
输入
第一行输入一个整数t，代表有t组样例:（ T≤30）
接下来的t行，都用一个整数n，表示楼梯有n级台阶（ 1≤n≤30）
输出

输出一个整数，表示跳到第n级台阶有多少种跳法。每个样例结果输出占一行。

样例输入 Copy
3
1
3
5
样例输出 Copy
1
4
16 */

// https://blog.csdn.net/qq_55624813/article/details/121316553?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-0-121316553-blog-80567180.pc_relevant_3mothn_strategy_recovery&spm=1001.2101.3001.4242.1&utm_relevant_index=3
#include<stdio.h>

int JumpSteps(int x);

int main()
{
    int t;
    while(scanf("%d",&t)!=EOF)
    {
        for(int i=0; i<t; i++)
        {
            int n;
            scanf("%d",&n);
            printf("%d\n",JumpSteps(n));
        }
    }
    return 0;
}

int JumpSteps(int x)
{
    int fx;
    if(x<2)
    {
        return x;
    }
    else
    {
        return 2*JumpSteps(x-1);
    }
}