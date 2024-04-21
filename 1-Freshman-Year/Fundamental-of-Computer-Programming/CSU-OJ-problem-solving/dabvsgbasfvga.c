#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    int h,m,s,n;
    while(scanf("%d:%d:%d+%d",&h,&m,&s,&n)!=EOF)
    {
        s=s+n;
        while(s>=60)
        {
                s-=60;
                m++;
                if(m>=60)
                {
                    m-=60;
                    h++;
                    if(h>=24)
                    {
                        h-=24;
                    }
                }
  
        }
            if(h<10)
            {
                printf("0");
        
            }
            printf("%d:",h);
            if(m<10)
            {
                printf("0");
            }
            printf("%d:",m);
            if(s<10)
            {
                printf("0");
            }
            printf("%d\n",s);
    }
    return 0;
}