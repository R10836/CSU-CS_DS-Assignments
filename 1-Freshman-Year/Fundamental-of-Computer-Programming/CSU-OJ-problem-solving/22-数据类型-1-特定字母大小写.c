#include<stdio.h>

int main()
{
    char a[40];
    while(gets(a)!=NULL)
    {
        for(int i=0; i<40; i++)
        {
            if(a[i]=='e' || a[i]=='r' || a[i]=='n')
            {
                a[i]-=32;
            }
            if(a[i]=='M' || a[i]=='I' || a[i]=='K' || a[i]=='A' || a[i]=='S')
            {
                a[i]+=32;
            }
        }
        puts(a);
    }
    return 0;
}

/*
问题 F: 22-数据类型-1-特定字母大小写
[命题人 : 219127]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
Eren和mikasa之间拥有强烈的羁绊，现在对于给出的任意一个字符串，要求将e，r，n这三个字母大写，原来就是大写的则保持不变；将m，i，k，a，s这五
个字母小写，原来就是小写的则保持不变。
输入
多组样例，每个测试样例一行，每行为一个字符串。（字符串长度小于40）
输出
将指定字母进行大小写转换之后的结果。
样例输入 Copy
bhFjbhFNdnknjk./]’]’gfjdsfnmv
ErEnJaegerMikasaAckerman
ereMIKAS
EREmikas
样例输出 Copy
bhFjbhFNdNkNjk./]’]’gfjdsfNmv
ERENJaEgERmikasaackERmaN
EREmikas
EREmikas
*/