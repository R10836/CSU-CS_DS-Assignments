#include<stdio.h>
#include<string.h>

int main()
{
    char a[100000];
    scanf("%s",&a);//gets(a);OJ会说运行错误，为啥？？？？？
    int len=strlen(a);
    for(int i=0; i<len-1; )
    {
        if(a[i] != a[i+1])
        {
            i++;
        }
        else//(a[i] == a[i+1])
        {
            for(int j=i; j<len; j++)
            {
                a[j]=a[j+2];
            }
            len-=2;
            i--;//画龙点睛：消掉之后再回退一格
        }
    }
    for(int i=0; i<len; i++)
    {
        printf("%c",a[i]);
    }
    return 0;
}

/*
问题 A: 22-字符串-2-相邻相同字母删除
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
小南现在有一段由小写字母组成的文本s，他每天的工作就是找到文本中两个相邻并且相同的字母，然后删除它们。注意这个删除过程可能是重复的，比如:
"abbac"->"aac"->"c"。 也就是说最终的文本中没有相邻相同的字母。
输入
单样例。每个测试文件只有一个样例输入，输入的一行文本的长度len满足1≤len≤105。
输出
输出一行，代表处理后的文本。
样例输入 Copy
abbbac
样例输出 Copy
abac
*/