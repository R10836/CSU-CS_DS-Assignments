#include<stdio.h>
#include<string.h>

int main()
{
    char a[10],b[10];
    while(scanf("%s %s",a,b)!=EOF)
    {
        int len1=strlen(a);
        int len2=strlen(b);
        if(len1 >= len2)
        {
            for(int i=0; i<len2; i++)
            {
                a[len1-1-i]+=(b[len2-1-i]-48);//不要忘了-48 ！！！！！！！！！！！！！！！！！！！！！
            }
            int flag=0;
            for(int i=0; i<len1; i++)
            {
                if(a[i] > '9')
                {
                    a[i]-=10;
                }
                if(a[i] != '0')
                {
                    flag=1;
                }
                if(flag==1)
                {
                    printf("%c",a[i]);
                }
                if(flag==0 && i==len1-1)//败在了思维的不严密！
                {
                    printf("0");
                }
            }
            printf("\n");
        }
        else
        {
            for(int i=0; i<len1; i++)
            {
                b[len2-1-i]+=(a[len1-1-i]-48);
            }
            int flag=0;
            for(int i=0; i<len2; i++)
            {
                if(b[i] > '9')
                {
                    b[i]-=10;
                }
                if(b[i] != '0')
                {
                    flag=1;
                }
                if(flag==1)
                {
                    printf("%c",b[i]);
                }
                if(flag==0 && i==len2-1)
                {
                    printf("0");
                }
            }
            printf("\n");
        }
    }
    return 0;
}

/*
问题 AI: 21级补考-按位相加（10分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
小南很喜欢做a+b，他但经常忘记进位，所以他算88+12=90,而不是100。现在老师给了小南一些a+b的算式，请问他算出来会是什么？
输入
多组样例。每行一个样例，是用空格分开的两个整数a和b（0≤a,b≤109）。
输出


对于每一个样例，输出相加后的结果，注意不要输出非0整数的前导0。每个输出占一行。

样例输入 Copy
5 6
55 6
81 22
样例输出 Copy
1
51
3
*/

/*
#include<stdio.h>
#include<string.h>

int main()
{
    char a[10],b[10];
    while(scanf("%s %s",a,b)!=EOF)
    {
        int len1=strlen(a);
        int len2=strlen(b);
        if(len1 >= len2)
        {
            for(int i=0; i<len2; i++)
            {
                a[len1-1-i]+=(b[len2-1-i]-48);
            }
            int flag=0;
            for(int i=0; i<len1; i++)
            {
                if(a[i] > '9')
                {
                    a[i]-=10;
                }
                if(a[i] != '0')
                {
                    flag=1;
                }
                if(flag==1)
                {
                    printf("%c",a[i]);
                }
                if(flag==0 && i==len1-1)
                {
                    printf("0");
                }
            }
            printf("\n");
        }
        else
        {
            for(int i=0; i<len1; i++)
            {
                b[len2-1-i]+=(a[len1-1-i]-48);
            }
            int flag=0;
            for(int i=0; i<len2; i++)
            {
                if(b[i] > '9')
                {
                    b[i]-=10;
                }
                if(b[i] != '0')
                {
                    flag=1;
                }
                if(flag==1)
                {
                    printf("%c",b[i]);
                }
                if(flag==0 && i==len2-1)
                {
                    printf("0");
                }
            }
            printf("\n");
        }
    }
    return 0;
}
*/