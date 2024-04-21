#include<stdio.h>


int main()
{
    char a[80];
    while(gets(a)!=NULL)
    {
        int len=strlen(a);
        for(int j=0; j<len; j++)
        {
            if(a[j]<='z' && a[j]>='a')
            {
                a[j]=-a[j]+'a'+'z';
            }
            else if(a[j]<='Z' && a[j]>='A')
            {
                a[j]=-a[j]+'A'+'Z';
            }
        }
            puts(a);
    }
    return 0;
}

/*
问题 A: 22-循环-1-字符串反码
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 32 MB

题目描述
字符反码的定义：对于字符x和它的反码y之间满足如下关系：
（1）如果x是小写字母字符，则x和字符'a’的距离等于它的反码y和字符'z’ 的距离；
（2）如果x是大写字母字符，则x和字符'A’的距离等于它的反码y和字符'Z’的距离；
（3）如果x不是小写字母也不是大写字母，它的反码y等于x。
例如：'a’的反码是'z’；'c’的反码是'x’；'W’的反码是'D’；'1’的反码还是'1’；'$'的反码还是'$'。
一个字符串的反码定义为其所有字符的反码，你的任务就是计算出给定字符串的反码。
输入
输入每行都是一个字符串，字符串长度不超过 80 个字符。
输出
对于输入的每个字符串，输出其反码。
样例输入 Copy
Hello 
样例输出 Copy
Svool 
*/