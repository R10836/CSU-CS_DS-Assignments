#include<stdio.h>
#include<string.h>
#include<math.h>

#define cha 3

int isPrime(int x);

int main()
{
    char s[1001];
    int a[400];
    while(scanf("%s",s)!=EOF)
    {
        int len=strlen(s);

        int i,p;
        for(i=0,p=0; p<len-cha; i++,p+=3)
        {
            a[i]=(s[p]-48)*100+(s[p+1]-48)*10+(s[p+2]-48);
        }
        a[i]=0;
        for(int j=0; j<len-p; j++)
        {
            a[i]+=((s[len-1-j]-48)*pow(10,j));
        }

        for(int j=0; j<=i; j++)
        {
            if(isPrime(a[j])==0)
            {
                printf("NO\n");
                break;
            }
            if(j==i)
            {
                printf("YES\n");
            }
        }
    }
    return 0;
}

//判断一个数是不是质数/素数直接套用（要加#include<math.h>）
int isPrime(int x)
{//是素数则返回值1，不是则返回0
    if(x==1 || x==0)
    {
        return 0;
    }
    for(int j=2; j<=sqrt(x); j++)
    {
        if(x%j==0)//当余数不零时才是素数
        {
            return 0;
        }
    }
    return 1;
}

/*
问题 N: 20级期末机试2-素数串（10分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
中南CC君最近迷上了素数，素数是指除了1和本身外不能被其他数整除的正整数，2是最小的素数。他发现有一种叫素数串的整数很有意思。它要求从该整数左边开始，每取3位数字构成的整数是素数，剩余的不够3位的整数也是素数。如23311317就是素数串，因为233,113,17都是素数，但是233111就不是，因为111不是素数。给你一个n（1≤n≤101000），你能帮CC君判断一下是素数串整数吗？
输入
多组样例。每行一个样例包含一个整数n。
输出
对于每一个输入的n，输出一个结果，如果是素数串整数，输出"YES"，否则输出"NO"。每个输出占一行。
样例输入 Copy
2
3892
100733
样例输出 Copy
YES
YES
NO
*/