#include<stdio.h>

int main()
{
    int T;
    while(scanf("%d",&T)!=EOF)
    {
        for(int ii=0; ii<T; ii++)
        {
            int n;
            scanf("%d",&n);
            //打印瓶盖
            for(int i=0; i<n-1; i++)
            {
                printf("-");
            }
            printf("\n");
            //打印上半空气部分
            printf("\\");
            for(int i=0; i<n-1-2; i++)
            {
                printf(" ");
            }
            printf("/\n");
            //打印上半沙子部分
            for(int i=0; i<n/2-2; i++)
            {
                for(int j=0; j<i+1; j++)
                {
                    printf(" ");
                }
                printf("\\");
                for(int k=0; k<2*(n/2-2-i)-1; k++)
                {
                    printf("*");
                }
                printf("/\n");
            }
            //打印下半部分
            for(int i=0; i<n/2-1; i++)
            {
                for(int j=0; j<n/2-1-i-1; j++)
                {
                    printf(" ");
                }
                printf("/");
                for(int j=0; j<i; j++)
                {
                    printf(" ");
                }
                printf("*");
                for(int j=0; j<i; j++)
                {
                    printf(" ");
                }
                printf("\\\n");
            }
            //打印瓶底
            for(int i=0; i<n-1; i++)
            {
                printf("-");
            }
            printf("\n\n");//我操你妈！！！！！！！！！！
        }
    }    
    return 0;
}

/*
问题 B: 20级期中机试-小帅的沙漏（10分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述


小帅用字符输出一个如同样例格式的沙漏的图形。要求如下：

用-做上下底
用\和/做斜边
用*表示沙子
上层沙子空一行，其他行填满；下层沙子只有中间一列。
上下底的行首无空格，所有行的行末无空格。
输入
第一行是样例数T(1≤T≤75)。 以后的每行一个样例，是一个整数n(6≤n≤80)，n是偶数，表示沙漏的行数。
输出
每行输出一个对应的图形，每个样例之后输出一个空行。 

样例输入 Copy
2
6
8
样例输出 Copy
-----
\   /
 \*/
 /*\
/ * \
-----

// -------
// \     /
//  \***/
//   \*/
//   /*\
//  / * \
// /  *  \
// -------
