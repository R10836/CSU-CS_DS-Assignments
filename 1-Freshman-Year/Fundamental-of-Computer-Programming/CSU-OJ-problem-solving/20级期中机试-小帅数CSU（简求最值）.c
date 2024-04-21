#include<stdio.h>
#include<string.h>

int main()
{
    char a[1000];
    while(scanf("%s",a)!=EOF)
    {
        int min,c=0,s=0,u=0;
        for(int i=0; i<strlen(a); i++)
        {
            if(a[i]=='C')
            {
                c++;
            }
            if(a[i]=='S')
            {
                s++;
            }
            if(a[i]=='U')
            {
                u++;
            }
        }
        min=c;//复习求最值的方法！！！！！！！！！！1
        if(min>s){min=s;}
        if(min>u){min=u;}
        printf("%d\n",min);
    }
    return 0;
}

/*
问题 F: 20级期中机试-小帅数CSU（20分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
给小帅一个字符串，由大写字母构成，每个字母限用一次，请问最多能组成多少个CSU。
输入
多组样例，每行一个字符串
输出
输出一个数字，能组成最多的CSU的个数
样例输入 Copy
CSU
CCC
CCSSUU
样例输出 Copy
1
0
2
*/