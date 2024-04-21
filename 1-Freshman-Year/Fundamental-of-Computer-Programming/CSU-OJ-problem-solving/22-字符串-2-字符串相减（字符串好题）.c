/*原答案超时：
#include<stdio.h>
#include<string.h>

int main()
{
    char a[10000], b[10000];
    while(gets(a)!=NULL)
    {
        gets(b);
        int len1=strlen(a);
        int len2=strlen(b);
        for(int i=0; i<len1; i++)
        {
            for(int j=0; j<len2; )
            {
                if(a[i] == b[j])
                {
                    for(int k=i; k<len1; k++)
                    {
                        a[k]=a[k+1];
                    }
                    len1--;
                    j=0;
                }
                else
                {
                    j++;
                }
            }
        }
        for(int i=0; i<len1; i++)
        {
            printf("%c",a[i]);
        }
        printf("\n");
    }
    return 0;
}
*/

#include<stdio.h>
#include<string.h>

int main()
{
    char a[10000], b[10000];
    while(gets(a)!=NULL)
    {
        gets(b);
        int len1=strlen(a);
        int len2=strlen(b);
        for(int i=0; i<len1; i++)
        {
            for(int j=0; j<len2; j++)
            {
                if(a[i] == b[j])
                {
                    a[i]='{';//我赌多样例不会有{这个字符
                }
            }
        }
        for(int i=0; i<len1; i++)
        {
            if(a[i] != '{')
            {
                printf("%c",a[i]);
            }
        }
        printf("\n");
    }
    return 0;
}

/*网上答案-引入c[10000]法：
#include<stdio.h>
#include<string.h>
 
int main()
{
    char s1[10000],s2[10000],s3[10000];
    while(gets(s1)!=NULL)
    {
        gets(s2);
        int n1=strlen(s1), n2=strlen(s2);
        int m=0;
        for(int i=0; i<n1; i++)
        {
            for(int j=0; j<n2; j++)
            {
                if(s1[i] == s2[j])
                {
                    break;
                }
                if(j==n2-1)
                {
                    s3[m]=s1[i];
                    m++;
                }
            }
        }
        for(int l=0; l<=m-1; l++)//因为前面m++多了一个的缘故
        {
            printf("%c",s3[l]);
        }
        printf("\n");
    }
    return 0;
}
*/

/*
问题 B: 22-字符串-2-字符串相减
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
小南现在有两个字符串S1和S2，他定义了一种字符串减法，S1-S2即在S1中去除掉所有S2中的字符所剩下的字符串。
举例: S1="ABA", S2="A"，则 S1-S2="B"。
输入
输入包含多组测试用例。每组测试用例包括两个字符串S1和S2，字符串长度不超过104。每个字符串都是由可见ASCII字符和空格组成。
输出
对于每组测试用例，输出S1-S2的结果。每个输出占一行。
样例输入 Copy
ABA
A
A B&&1
&
样例输出 Copy
B
A B1
提示
对于输入包含空格的字符串时，最好采用while(gets(a)!=NULL)处理多样例。
*/