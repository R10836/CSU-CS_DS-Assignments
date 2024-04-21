#include<stdio.h>
#include<math.h>

int isPrime(int);
int isHuiWen(int);

int main()
{
    int l,r;
    while(scanf("%d %d",&l,&r)!=EOF)
    {
        int num=0;
        for(int i=l; i<=r; i++)
        {
            if(isHuiWen(i)==1 && isPrime(i)==1)
            {
                num++;
            }
        }
        printf("%d\n",num);
    }
    return 0;
}

//以后判断一个数是不是质数/素数直接套用（要加#include<math.h>）
int isPrime(int x)
{
    if(x==1)
    {
        return 0;
    }
    for(int j=2; j<=sqrt(x); j++)
    {
        if(x%j==0)//栽在了：当余数不零时才是素数！！！！！
        {
            return 0;
        }
    }
    return 1;
}

////以后判断一个数是不是回文数直接套用（要加#include<math.h>）
int isHuiWen(int x)
{
    int x2=x;

    int wei;
    for(wei=0; x2>0; wei++)
    {
        x2/=10;
    }

    int sum=0;
    int x3=x;
    for(int i=1; x3>0; i++)
    {
        int n=x3%10;
        sum+=(n*pow(10,wei-i));
        x3/=10;
    }

    if(sum==x)
    {
        return 1;
    }
    return 0;
}

/*
问题 B: 22-函数-2-回文素数
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
如果一个整数只能被1和自己整除，就称这个数是素数。 ps: 1不是素数。
如果一个数正着反着都是一样，就称为这个数是回文数。例如:6, 66, 606, 6666
如果一个数字既是素数也是回文数，就称这个数是回文素数 。
老师现在给小南一个任务，让他求出给定的区间[L, R]（包括边界L和R）内有多少个回文素数。你能帮助他吗？
输入
多组测试用例。每组测试用例输入一行，包含两个正整数L和R（1≤L≤R≤1000）。
输出
对于每个测试样例，输出一个整数，代表 [L,R] 内回文素数的数量。每个结果占一行。
样例输入 Copy
1 10
100 120
样例输出 Copy
4
1
*/