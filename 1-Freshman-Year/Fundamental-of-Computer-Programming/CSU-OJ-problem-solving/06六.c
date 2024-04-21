#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

struct csu
{
    char t[25];
    int jing;
    int sum;
}team[100],t;

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        int  x,y;
        for(int pp=0; pp<n*(n-1)/2; pp++)
        {
            int ch,i=0;
            while((ch=getchar())!=':')
            {//在读入换行符时才能终止，而不是空格
                if(i < n)
                {
                    team[pp].t[i++]=ch;
                }
            }
            scanf("%s",team[pp].t[i++]);
            scanf(" %d:%d",&x,&y);
        }
        
    }
    return 0;
}