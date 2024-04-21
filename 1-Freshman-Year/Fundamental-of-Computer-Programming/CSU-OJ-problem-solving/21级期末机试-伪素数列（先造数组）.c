/*
第一次我的超时了，为什么呢？

若是一开始把前5000个放一个数组里，那么多样例时就只需要输出即可
甚至不需要计算

而像我一样，虽然前5000个算的还挺快，但是多样例下来会很慢，
因为每次输入都是计算+输出

总结：有多样例的超时：
应该 计算+输出+输出+输出+。。。
而不是 计算+输出+计算+输出+计算+输出。。。
*/
#include<stdio.h>

int isPrime(int x);
int fuck(int x);

int main()
{
    int a[5000];
    for(int i=2,m=0; m<=5000; i++)
    {
        if(fuck(i)==1)
        {
            a[m]=i;
            m++;
        }
        else if(isPrime(i)==1)
        {
            a[m]=i;
            m++;
        }
    }
    int k;
    while(scanf("%d",&k)!=EOF)
    {
        printf("%d\n",a[k-1]);
    }
}

//判断一个数是不是质数/素数直接套用（要加#include<math.h>）
int isPrime(int x)
{//是素数则返回值1，不是则返回0
    for(int j=2; j*j<=x; j++)
    {
        if(x%j==0)//当余数不零时才是素数
        {
            return 0;
        }
    }
    return 1;
}

//伪素数
int fuck(int x)
{
    while(x != 0)
    {
        if(x%10!=2&&x%10!=3&&x%10!=5&&x%10!=7)
        {
            return 0;
        }
        x/=10;
    }
    return 1;
}
/*
#include<stdio.h>

int isPrime(int x);
int fuck(int x);

int main()
{
    int k;
    while(scanf("%d",&k)!=EOF)
    {
        int i=2,no=0;
        while(1)
        {
            if(fuck(i)==1)
            {
                no++;
            }
            else if(isPrime(i)==1)
            {
                no++;
            }
            if(no==k)
            {
                break;
            }
            i++;
        }
        printf("%d\n",i);
    }
    return 0;
}

//判断一个数是不是质数/素数直接套用（要加#include<math.h>）
int isPrime(int x)
{//是素数则返回值1，不是则返回0
    for(int j=2; j*j<=x; j++)
    {
        if(x%j==0)//当余数不零时才是素数
        {
            return 0;
        }
    }
    return 1;
}

int fuck(int x)
{
    while(x != 0)
    {
        if(x%10!=2&&x%10!=3&&x%10!=5&&x%10!=7)
        {
            return 0;
        }
        x/=10;
    }
    return 1;
}
*/

/*
问题 AB: 21级期末机试-伪素数列（20分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
如果一个正整数A是素数，或者A的每一位数字都是素数，我们称A为伪素数。例如，23是素数，235的每一位数字都是素数，所以23和235都是伪素数，而135不是素数，其中的数字1不是素数，所以135不是伪素数。老师给了小南一个任务，让他在一个称作伪素数列的集合An={2,3,5,7,11,13,17,19,22,23,25,…}中快速找到第k个伪素数，聪明的你能帮他完成任务吗？
输入
多组样例。每行输入一个样例包括一个正整数k（1≤k≤5000）。
输出
对每一个输入的k，输出一个正整数x，表示数列An中的第k项的值，其值范围不会超过int型。每个输出占一行。
样例输入 Copy
1
5
10
样例输出 Copy
2
11
23
*/