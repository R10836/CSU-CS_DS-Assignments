#include<stdio.h>//跌在了不要一味的复制粘贴 + 拼写一定要正确，swich是错的

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        char str[n];
        scanf("%s",str);
        int left=0, right=0;
        for(int i=0; i<n; i++)
        {
            if(str[i] == 'L')
            {
                left++;
            }
            else if(str[i] == 'R')
            {
                right++;
            }
        }
        char now;
        if(left > right)
        {
            int all=left-right;
            switch(all%4)
            {
                case 0:now='N';break;
                case 1:now='W';break;
                case 2:now='S';break;
                case 3:now='E';break;
            }
        }
        else if(left < right)
        {
            int all=right-left;
            switch(all%4)
            {
                case 0:now='N';break;
                case 1:now='E';break;
                case 2:now='S';break;
                case 3:now='W';break;
            }
        }
        else
        {
            now='N';
        }
        printf("%c\n",now);
    }
    return 0;
}

/*
问题 T: 21级期中机试-东南西北（20分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述

德乃人之本，孝为德之先，小南经常利用周末去敬老院进行志愿服务活动。这次他去了一个新的敬老院，回家路上迷路了，只记得出门的时候面向北方，中间左转或者右转了若干次。为了确定自己的位置，她需要知道自己现在面向哪个方向，请你帮帮她。（说明：如果面向北方，按照顺时针右转的方向依次为东方、南方和西方）

输入

多组样例。每组样例包括两行输入，第一行包含一个正整数n（0<n≤1000），表示转方向的次数。接下来的第二行包含一个长度为n的字符串，只由L和R组成，L表示向左转，R表示向右转。


输出
对于每一组样例，输出一个字母，代表小南最后面向的方向，N表示北，S表示南，E表示东，W表示西。每个输出占一行。

样例输入 Copy
1
L
1
R
3
LRR
样例输出 Copy
W
E
E
*/