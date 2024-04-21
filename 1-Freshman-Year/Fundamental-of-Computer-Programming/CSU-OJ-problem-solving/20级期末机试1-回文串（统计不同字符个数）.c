#include<stdio.h>
#include<string.h>

int main()
{
    char s[50];
    while(scanf("%s",s)!=EOF)
    {
        int len=strlen(s);
        int flag=0;
        for(int i=0; i<len/2; i++)
        {
            if(s[i]==s[len-1-i])
            {
                ;
            }
            else
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            printf("NO\n");
        }
        else
        {
            printf("YES ");
            //以后找重复字符可以借鉴！！！
            int sum=len;
            for(int i=1; i<len; i++)
            {
                for(int j=i-1; j>=0; j--)
                {
                    if(s[i]==s[j])
                    {
                        sum--;
                        break;//一计定天下
                    }
                }
            }
            printf("%d\n",sum);
        }
    }
    return 0;
}

/*
问题 I: 20级期末机试1-回文串（20分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
中南CC君特别喜欢古诗词，最欣赏清代女诗人吴绛雪写的一首回文诗《春》“莺啼岸柳弄春晴夜月明”，只用了十个字，对应的却是一首七言绝句为：莺啼岸柳弄春晴，柳弄春晴夜月明。明月夜晴春弄柳，晴春弄柳岸啼莺。
CC君由回文诗联想到了最近学校交给他的一个关于回文字符串的任务：对一个给定的只包含小写字母的字符串进行回文判定，并统计回文字母串中不同字母的个数。回文是指顺读和逆读一样。你能帮他完成这个任务吗？
输入
多组样例。每行一个样例包含仅由小写字母组成的字符串，最多50字母。
输出
对于每一个输入的样例，输出一个结果。如果是回文串，则输出“YES”和不同字母的个数，中间用空格分开；如果不是回文串，则输出“NO”。
样例输入 Copy
abcdefgdefghijjihgfedgfedcba
wbcddcbw
goodlucktestover
样例输出 Copy
YES 10
YES 4
NO
*/