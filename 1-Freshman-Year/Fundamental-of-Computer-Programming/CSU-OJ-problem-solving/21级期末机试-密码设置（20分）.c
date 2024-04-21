#include<stdio.h>
#include<string.h>

int main()
{
    char s[30];
    while(scanf("%s",s)!=EOF)
    {
        int len=strlen(s);
        if(len < 8)
        {
            printf("no\n");
            continue;
        }
        int num=0, big=0, sma=0, spc=0;
        for(int i=0; i<len; i++)
        {
            if(s[i] <= 57 && s[i] >= 48)
            {
                num=1;
            }
            if(s[i] <= 90 && s[i] >= 65)
            {
                big=1;
            }
            if(s[i] <= 122 && s[i] >= 97)
            {
                sma=1;
            }
            if(s[i]=='!'||s[i]=='@'||s[i]=='#'||s[i]=='*'||s[i]=='~')
            {
                spc=1;
            }
        }
        if(num+big+sma+spc >= 3)
        {
            printf("yes\n");
        }
        else
        {
            printf("no\n");
        }
    }
    return 0;
}

/*
问题 AA: 21级期末机试-密码设置（20分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
小南有个密码本，详细记录着她在每个网站上的密码，但是有的密码设置可能存在安全问题，她想请聪明的你帮她看看密码设置是否正确。安全密码的判断有以下几个规则：
（1）密码长度必须≥8
（2）包含数字
（3）包含大写字母
（4）包含小写字母
（5）至少包含6个特殊字符（! @ # $ * ~）中的一个
以上规则，除（1）必须满足外，其他四个条件至少满足其中三个才是安全的密码。
输入
多组样例。每行一个样例，输入一个字符串S代表密码，字符串S的长度len(S)满足：1≤len(S)≤30，且只包含密码设置要求的数字、字母和特殊字符，无其他非法字符。
输出
对于每一组样例，输出一个判断结果。如果满足安全密码的设置要求则输出yes，不满足则输出no。每个输出占一行。
样例输入 Copy
ttttttttt
123Aa~
123456QqWe
aQwe!1234
123$#abc
样例输出 Copy
no
no
yes
yes
yes
*/