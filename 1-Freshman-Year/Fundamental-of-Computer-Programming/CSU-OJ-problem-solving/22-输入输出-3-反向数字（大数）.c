/*
问题 A: 22-输入输出-3-反向数字
[命题人 : 219127]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
题主是韦神粉丝，想知道一个数字的反向数字，现给定一个整数a，请将该数各个位上数字反转得到一个新数。新数也应满足整数的常见形式，即除非给定的原数为零，否则反转后得到的新数的最高位数字不应为零。a反转得到的数保持符号位不变。
输入
多组样例，每个测试样例一行，整数a。
输出
反向数字
样例输入 Copy
235
-130
样例输出 Copy
532
-31
*/

/*
#include<stdio.h>
#include<math.h>

int turn(int x);
int wei(int x);

int main()
{
    int a;
    while(scanf("%d",&a)!=EOF)
    {
        printf("%d\n",turn(a));
    }
    return 0;
}

int turn(int x)
{
    int w=wei(x);
    int m=x, n, sn, sum=0;
    for(int i=0; i<w; )
    {
        n=m%10;
        m=m/10;
        i++;
        sn=n*pow(10,w-i);
        sum+=sn;

    }
    return sum;
}

int wei(int x)
{
    int i;
    for(i=0;x!=0;i++)
    {
        x/=10;
    }
    return i;
}
*/

//数组解法：
#include<stdio.h>
#include<math.h>

int main()
{
    char s1[1000];
    while(gets(s1)!=NULL)
    {
        if(s1[0]!='-')
        {
            char s2[1000];
            int w=strlen(s1);
            for(int i=0; i<w; i++)
            {
                s2[i]=s1[w-1-i];
            }
            int flag=0;//先默认开头为0
            for(int i=0; i<w; i++)
            {
                if(s2[i]!='0')//如果开头不是0，直到开头不是0才能改为flag1
                {
                    flag=1;//改为开头不是0
                }
                if(flag==1)
                {
                    printf("%c",s2[i]);
                }
            }
            printf("\n");
        }
        else//(s1[0]=='-')
        {
            printf("%c",s1[0]);
            char s2[1000];
            int w=strlen(s1)-1;
            for(int i=1; i<w+1; i++)
            {
                s2[i]=s1[w-i+1];
            }
            int flag=0;//先默认开头为0
            for(int i=1; i<w+1; i++)
            {
                if(s2[i]!='0')//如果开头不是0，直到开头不是0才能改为flag1
                {
                    flag=1;//改为开头不是0
                }
                if(flag==1)
                {
                    printf("%c",s2[i]);
                }
            }
            printf("\n");
        }
    }
    return 0;
}