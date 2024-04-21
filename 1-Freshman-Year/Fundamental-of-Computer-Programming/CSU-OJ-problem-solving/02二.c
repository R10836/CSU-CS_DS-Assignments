#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>


int main()
{
    char a[1001],b[1001],c[1001];
    while(scanf("%s %s",a,b)!=EOF)
    {
        int len1=strlen(a);
        int len2=strlen(b);
        if(len1>=len2)
        {
            for(int i=0; i<len1; i++)
            {
                if(i<len2)
                {
                a[i]=b[i]-97+a[i]-97;
                if(a[i]>=26)
                {
                    a[i]-=26;
                }
                }
                if(i>=len2)
                {
                    a[i]-=97;
                }
                printf("%c",a[i]+97);
            }
            printf("\n");
        }
        else
        {
            for(int i=0; i<len2; i++)
            {
                if(i<len1){
                b[i]=a[i]-97+b[i]-97;
                if(b[i]>=26)
                {
                    b[i]-=26;
                }
                }
                if(i>=len1)
                {
                    b[i]-=97;
                }
                printf("%c",b[i]+97);
            }
            printf("\n");
        }
        
    }
    return 0;
}