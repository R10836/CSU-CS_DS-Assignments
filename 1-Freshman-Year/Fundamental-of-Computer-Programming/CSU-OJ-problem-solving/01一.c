#include<stdio.h>//E8ei2WNZd1
#include<math.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    int a,b,c,d;
    while(scanf("%d.%d.%d.%d",&a,&b,&c,&d)!=EOF)
    {
        if(a>=0 && a<=255 && b>=0 && b<=255 && c>=0 && c<=255 && d>=0 && d<=255)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
    return 0;
}