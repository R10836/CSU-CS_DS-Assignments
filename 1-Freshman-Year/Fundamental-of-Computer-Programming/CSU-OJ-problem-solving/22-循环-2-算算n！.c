// 我的原答案：溢出问题
// 要按题上给的缩小数据的提示!现在是对的
#include<stdio.h>

int this(int x);

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        printf("%d\n",this(n));
    }
    return 0;
}

int this(int x)
{
    int y;
    if(x>=41)
    {
        y=0;
    }
    else
    {
        y=1;
        for(int i=x; i>=1; i--)
        {
            y*=i;
            y%=2009;
        }
    }
    return y;
}

/*
https://blog.csdn.net/hjd_love_zzt/article/details/43413373?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-43413373-blog-127467866.pc_relevant_landingrelevant&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-43413373-blog-127467866.pc_relevant_landingrelevant&utm_relevant_index=1

问题 I: 22-循环-2-算算n！
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
Alice：Bob你在干什么？
Bob：我在计算n的阶乘求余2009后的结果，即s=n!%2009
Alice：n有多大啊？
Bob：0≤n≤1000000000  
Alice：你疯了吧
Bob：放心，我会应用求余运算的性质的，即(axb)%c等价于((a%c)x(b%c))%c，而且n最多也才109 
输入
多组样例，输入一个整数n(0 ≤n≤109)
输出
输出一个数，表示输入数的阶乘求余2009后的结果。
样例输入 Copy
4
样例输出 Copy
24
提示
0! = 1, n! =n*(n-1)!
*/