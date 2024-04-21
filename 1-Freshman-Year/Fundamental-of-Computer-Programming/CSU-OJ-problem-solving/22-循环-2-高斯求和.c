/*
问题 H: 22-循环-2-高斯求和
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
C语言学到循环了，老师给了小南一个任务，就是给定一个n，让让小南快速计算出1+2+……+10n，其中(0≤n≤1000)。显然，当n较大时，直接用循环编写程序计算可能要花很长的时间。这个时候小南想起数学王子高斯小时候就能利用规律很快的将1+2+……+100算出来，于是小南也想利用这个规律完成老师的任务，你能帮他实现吗？
输入
多组样例，样例数由输入的第一行给出。即第一行输入一个整数t，表示有t个样例。接下来的t行，每行输入一个样例包括一个正整数n（0≤n≤1000）。


输出
输出t行，每一行对应一个输入的n，输出对应的结果。

样例输入 Copy
2
1
2
样例输出 Copy
55
5050
*/


/* 
#include<stdio.h>
#include<math.h>

long long int godsum(int n);

int main()
{
    int t;
    while(scanf("%d",&t)!=EOF)
    {
        for(int i=0;i<t;i++)
        {
            int n;
            scanf("%d",&n);
            printf("%lld\n",fuck(n));
        }
    }
    return 0;
}

long long int godsum(int n)
{
    long long int m=pow(10,n);
    return m*(m+1)/2;
}
*/

#include<stdio.h>
#include<math.h>

int main()
{
    int t;
    while(scanf("%d",&t)!=EOF)
    {
        for(int i=0;i<t;i++)
        {
            int n;
            scanf("%d",&n);
            if(n==0)
            {
                printf("1\n");
            }
            else
            {
            int a[2000]={0};
            a[0]=5;
            a[n]=5;
            for(int i=0;i<2*n;i++)
                printf("%d",a[i]);
                printf("\n");
            }
        }
    }
    return 0;
}

/*由答案
1
55
5050
500500
50005000
找规律，跟高斯没有半毛钱关系。。。
*/
