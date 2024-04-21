//OJ会超时，但是时间足够没什么大问题
#include<stdio.h>
#include<string.h>

int isHuiWenChar(char str[], int len);

int main()
{
    char n[10010];
    while(scanf("%s",n)!=EOF)
    {
        int len=strlen(n);
        while(1)
        {
            int i=len-1;
            n[i]++;
            int i3=i;
            while(n[i3] == ':')//字符串数组自加这样进位
            {
                n[i3]='0';
                if(i3 == 0)//当进位时满了一位
                {
                    len++;
                    for(int j=len-1; j>=1; j--)
                    {
                        n[j]=n[j-1];
                    }
                    n[i3]='1';
                }
                i3--;
                n[i3]++;
            }
            if(isHuiWenChar(n, len))
            {
                break;
            }
        }
        for(int i=0; i<len; i++)
        {
            printf("%c",n[i]);
        }
        printf("\n");
    }
    return 0;
}

//判断是不是回文数字符串
int isHuiWenChar(char str[], int len)
{//(数组名,数组长度)
    for(int i=0; i<len/2; i++)
    {
        if(str[i] != str[len-1-i])
        {
            return 0;
        }
    }
    return 1;
}

/*
#include<stdio.h>
#include<string.h>
  
char a[10010];
int main(){
    while(scanf("%s",a)!=EOF)
        {
        int len=strlen(a);
        int flag=0;
        for(int i=len/2-1;i>=0;i--)
        {
            if(a[i]>a[len-i-1])
                {
                  flag=1;
                  break;
                }
            else
            if(a[i]<a[len-i-1])
            {
                flag=0;
                break;
            }
        }
        if(!flag)
            {
            for(int i=(len-1)/2;i>=0;i--)
            {
                a[i]++;
                if(a[i]>'9')
                  a[i]='0';
                else break;
            }
            if(a[0]=='0')
            {
                a[0]='1';
                len++;
                a[len/2]='0';
            }
        }
        for(int i=0;i<len/2;i++)
            printf("%c",a[i]);
        for(int i=(len+1)/2-1;i>=0;i--)
            printf("%c",a[i]);
        printf("\n");
    }
    return 0;
}
*/

/*
问题 F: 22-字符串-3-最小回文串
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 32 MB

题目描述
回文数是从前往后和从后往前得到的数是相同的。小南接到老师布置的任务，就是对给定的正整数n，找到比n大的最小的那个回文数p。由于n（0 <n< 1010000）可能是一个很大的数，所以只能用字符串来处理。你能帮他编写一个程序实现吗？
输入
多组样例。每组样例输入一个正整数n（0 <n< 1010000），并且n不会有前导0。
输出
对于每组输入，输出比n大的最小的那个回文数p。每个结果占一行。
样例输入 Copy
44
3
175
9
99
1331
19991
样例输出 Copy
55
4
181
11
101
1441
20002
*/