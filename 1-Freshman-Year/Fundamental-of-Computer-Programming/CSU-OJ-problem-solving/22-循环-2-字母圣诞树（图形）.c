/*
1、 此题核心在于输入时要求每个样例占一行，故是scanf(" %c",&a[k]);
    还是scanf没学懂学会
    要是没有那个空格，则输入为3ABC时才正确
    要想3 地输入，则要加那个空格。
        A
        B
        C

2、此外，做题时，先分析清楚变量之间的关系，手写清楚循环结构在敲键盘
*/

#include<stdio.h>

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        char a[n];//说明oj可过这样的数组
//int m;char a[m];//所以oj不可以过这样的数组（运行错误50%）
        int k;
        for(k=1; k<=n; k++)
        {
            scanf(" %c",&a[k]);

            for(int j=1; j<=k; j++)
            {
                for(int i=0; i<k; i++)
                {
                    printf(" ");
                }
                printf("%c\n",a[j]);

                for(int i=0; i<k-j; i++)
                {
                    printf(" ");
                }
                for(int i=0; i<2*j+1; i++)
                {
                    printf("%c",a[j]);
                }
                printf("\n");
            }

        }
    }
    return 0;
}

/*
问题 H: 22-循环-2-字母圣诞树
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
打印一个字母圣诞树。
输入
多组样例，第一行为样例的个数，接下来每个样例是一个大写英文字母，占一行。
输出
输出对应的字母圣诞树，每行末尾没有空格，每个圣诞树的最后一行前无空格。
样例输入 Copy
3
A
B
C
样例输出 Copy
 A
AAA
  A
 AAA
  B
BBBBB
   A
  AAA
   B
 BBBBB
   C
CCCCCCC
*/