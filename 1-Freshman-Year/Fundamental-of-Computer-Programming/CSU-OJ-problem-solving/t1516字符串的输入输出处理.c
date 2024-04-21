#include<stdio.h>
#include<string.h>

int read_line(char str[], int n);

int main()
{
    char s[1000];
    int N;
    scanf("%d",&N);
    getchar();//吸收回车!！！关键之处!：这个get可以消掉打完数字输的那个回车
    for(int i=0; i<N; i++)
    {
        read_line(s,1000);//换成gets也对
        printf("%s\n\n",s);
    }
    while(scanf("%s",s)!=EOF)//scanf自带遇到空格完事的功能
    {
        printf("%s\n\n",s);
    }
    return 0;
}
//逐个字符读字符串【安全替代gets()】(该字符串的名字，该字符串数组的数组大小)
int read_line(char str[], int n)
{
    int ch,i=0;
    while((ch=getchar())!='\n')
    {//在读入换行符时才能终止，而不是空格
        if(i < n)
        {
            str[i++]=ch;
        }
    }
    str[i]='\0';//空字符
    return i;
}

/*
1516: 字符串的输入输出处理
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 64 MB

题目描述
字符串的输入输出处理。
输入
第一行是一个正整数N，最大为100。之后是多行字符串（行数大于N）， 每一行字符串可能含有空格，字符数不超过1000。
输出
先将输入中的前N行字符串（可能含有空格）原样输出，再将余下的字符串（不含有空格）以空格或回车分割依次按行输出。每行输出之间输出一个空行。
样例输入 Copy
2
www.njupt.edu.cn NUPT
A C M
N U P Ter
样例输出 Copy
www.njupt.edu.cn NUPT

A C M

N

U

P

Ter

来源/分类
字符串 
*/