#include<stdio.h>
#include<string.h>

void duihuan(char a[],char b[]);
int bplus(char x[],char y[]);

int main()
{
    char x[400],y[400];
    while(scanf("%s %s",x,y)!=EOF)
    {

        int k=bplus(x,y);

        for(int i=0;i<k;i++)
        {
            printf("%c",x[i]);
        }
        printf("\n");
    }
    return 0;
}

//两数组的交换(！使用时注意数组类型 和 数组容量！)
void duihuan(char a[],char b[])
{
    char c[400];
    strcpy(c,a);
    strcpy(a,b);
    strcpy(b,c);
}

//正整数大数相加,加出来是x
int bplus(char x[],char y[])
{//传出字符串长度
    int xlen=strlen(x);
    int ylen=strlen(y);
    if(xlen <= ylen)
    {
        duihuan(x,y);
        int t=xlen;
        xlen=ylen;
        ylen=t;
    }
    //一个for搞定版
    for(int i=xlen-1; i>=0; i--)
    {
        if(i > xlen-ylen-1)
        {
            x[i]+=y[i-(xlen-ylen)]-48;
        }
        if(x[i] > '9' && i!=0)
        {
            x[i]-=10;
            x[i-1]++;
        }
    }
    if(x[0] > '9')
    {
        xlen++;
        x[0]-=10;
        for(int i=xlen-1; i>0; i--)
        {
            x[i]=x[i-1];
        }
        x[0]='1';
    }
    return xlen;
}