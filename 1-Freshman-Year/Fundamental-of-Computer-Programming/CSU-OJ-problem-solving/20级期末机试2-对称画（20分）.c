#include<stdio.h>

int main()
{
    int t;
    while(scanf("%d",&t)!=EOF)
    {
        for(int k=0; k<t; k++)
        {
            int n;
            scanf("%d",&n);
            //
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n-1-i; j++)
                {
                    printf(" ");
                }
                char ss='a';
                for(int j=0; j<i; j++)
                {
                    printf("%c",ss);
                    ss++;
                }
                printf("%c",ss);
                for(int j=0; j<i; j++)
                {
                    ss--;
                    printf("%c",ss);
                }
                printf("\n");
            }
            //
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<i; j++)
                {
                    printf(" ");
                }
                printf("a");
                for(int j=0; j<2*(n-i-1)-1; j++)
                {
                    printf(" ");
                }
                if(i != n-1)
                {
                    printf("a\n");
                }
            }
            printf("\n\n");
        }
    }
    return 0;
}

/*
问题 M: 20级期末机试2-对称画（20分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
中南CC君是一个喜欢对称美的艺术家，经常用电脑打印一些对称图形。不过他只喜欢左右对称，不喜欢上下对称。他希望你帮他打印一幅满足他喜好的对称画。
输入
第一行是样例数T（1<T<9)。以后的每行一个样例，是一个整数n(1≤n≤26)，与对称画的大小有关。
输出
每行输出一个对应的对称画图形，图形中最长的行左边没有空格。每个样例之后输出一个空行。
样例输入 Copy
2
2
3
样例输出 Copy
 a 
aba
a a
 a 

  a  
 aba 
abcba
a   a
 a a 
  a  
*/