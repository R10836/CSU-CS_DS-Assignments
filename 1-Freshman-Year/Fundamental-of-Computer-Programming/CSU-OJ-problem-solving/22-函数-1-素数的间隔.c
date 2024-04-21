//栽在了没看清题目上！最浪费时间且可惜！！！

#include<stdio.h>
#include<math.h>

int isPrime(int x);

int main()
{
    int n; int a,b;
    scanf("%d",&n);
    for(int i=n; ;i--)
    {
        if(isPrime(i))
        {
            a=i;
            break;
        }
    }
    for(int i=n; ;i++)
    {
        if(isPrime(i))
        {
            b=i;
            break;
        }
    }
    printf("%d",b-a);
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

/*
问题 C: 22-函数-1-素数的间隔
[命题人 : admin]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
输入一个整数n，求它后一个素数和前一个素数的差值。输入是素数时输出0。n不超过1299709（第100000个素数）。例如，n=27时输出29-23=6。

输入
单样例，每次输入一个整数n。
输出
输出满足条件的素数之间的差值，如果输入的整数是素数，则输出0。
样例输入 Copy
27
样例输出 Copy
6
*/