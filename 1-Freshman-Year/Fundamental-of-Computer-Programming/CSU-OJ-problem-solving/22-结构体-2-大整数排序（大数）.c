/*
极其重要 / 大数比大小 / 经典例题
栽在了：
1：排序法最后交换的一定是本体，而不能再是结构体里面的东西
2：大数比大小：当成字符串时，若长度（数位）相等，那么要且仅要比出第一个不一样的字符，即跳出循环
ALL：循环不清楚、oj报错时、等等，一定要纸币带入循环看看，不要想当然
未完待续：。。。

*/
#include<stdio.h>
#include<string.h>

struct csu
{
    char a[1001];
    int len;
}x[200],t;//t应该在这里，且交换的一定是本体

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0; i<n; i++)
        {
            scanf("%s",x[i].a);
            x[i].len=strlen(x[i].a);
        }

        for(int i=0; i<n-1; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                if(x[i].len > x[j].len)
                {
                    t=x[i];
                    x[i]=x[j];
                    x[j]=t;
                }
                else if(x[i].len == x[j].len)
                {
                    for(int k=0; k<x[i].len; k++)
                    {//一定要注意当x[i].a[k]小于x[j].a[k]就千万不要往后比了，只有相等时才要接着往后走循环
                        if(x[i].a[k] > x[j].a[k])
                        {
                            t=x[i];
                            x[i]=x[j];
                            x[j]=t;
                            break;
                        }
                        else if(x[i].a[k] < x[j].a[k])
                        {
                            break;
                        }
                        else//(x[i].a[k] == x[j].a[k])
                        {
                            continue;
                        }
                    }
                }
                else//(x[i].len < x[j].len)
                {
                    continue;
                }
            }
        }
//其实完全可以把两个比较放一块出结果
        // for(int i=0; i<n-1; i++)
        // {
        //     for(int j=i+1; j<n; j++)
        //     {
        //         if(x[i].len == x[j].len)
        //         {
        //             for(int k=0; k<x[i].len; k++)
        //             {//一定要注意当x[i].a[k]小于x[j].a[k]就千万不要往后比了，只有相等时才要接着往后走循环
        //                 if(x[i].a[k] > x[j].a[k])
        //                 {
        //                     t=x[i];
        //                     x[i]=x[j];
        //                     x[j]=t;
        //                     break;
        //                 }
        //                 else if(x[i].a[k] < x[j].a[k])
        //                 {
        //                     break;
        //                 }
        //                 else//(x[i].a[k] == x[j].a[k])
        //                 {
        //                     continue;
        //                 }
        //             }
        //         }
        //     }
        // }

        for(int i=0; i<n; i++)
        {
            puts(x[i].a);
        }
    }
    return 0;
}

/*
问题 E: 22-结构体-2-大整数排序
[命题人 : 外部导入]
时间限制 : 2.000 sec  内存限制 : 128 MB

题目描述
小南有n个整数，这些整数都非常大，所以没有办法采用整数排序的方法处理，请聪明的你帮小南编写程序完成这些整数由小到大的排序。
输入
输入包含多组测试用例。
对于每一组测试用例，第一行包含一个整数n（0<n≤200）。 
接下来n行每行包含一个整数x  (0≤x≤101000）。
输出
对于每一组测试数据，输出排序后的结果。
样例输入 Copy
2
20
10
3
11111111111111111111111111111
22222222222222
33333333
样例输出 Copy
10
20
33333333
22222222222222
11111111111111111111111111111
*/