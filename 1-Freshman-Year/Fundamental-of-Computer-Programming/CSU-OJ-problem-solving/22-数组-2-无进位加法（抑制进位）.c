/*
问题 F: 22-数组-2-无进位加法
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
小南很喜欢做a+b，但是他经常忘记进位，所以他算88+12=90,而不是100。 现在你给了小南一些a+b的算式，请问他算出来会是什么？
输入
第一行是一个整数K，表示样例的个数。 每个样例占一行，为两个整数a,b，0≤a,b≤1e9。
输出
每行输出一个样例的结果,不要输出前导0。
样例输入 Copy
3
1 2
5 6
55 55
样例输出 Copy
3
1
0
*/

#include<stdio.h>

int newplus(int,int);

int main()
{
    int k;
    while(scanf("%d",&k)!=EOF)
    {
        int a,b;
        for(int i=0; i<k; i++)
        {
            scanf("%d%d",&a,&b);
            printf("%d\n",newplus(a,b));
        }
    }
    return 0;
}

int newplus(int a,int b)
{
    int x=a,y=b,t,sum=0,a3,b3,c3;
    if(x<y)
    {
        t=x;
        x=y;
        y=t;
    }
    for(int i=0; x!=0; i++)
    {
        a3=x%10;
        x/=10;
        b3=y%10;
        y/=10;
        c3=((a3+b3)%10)*pow(10,i);
        sum+=c3;
    }
    return sum;
}