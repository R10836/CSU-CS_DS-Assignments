#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
 
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        int a[n];
        int sum=0;
        int s[n];
        for(int i=0; i<n;i++)
        {
            scanf("%d",&a[i]);
            sum+=a[i];
            s[i]=sum;
        }
 
 
 
 
        int m;
        scanf("%d",&m);
        int b[m];
        for(int i=0;i<m; i++)
        {
            scanf("%d",&b[i]);
            for(int j=0; j<n; j++)
            {
                if(b[i]<=s[j])
                {
                    printf("%d",j+1);
                    if(i!=m)
                    {
                        printf("\n");
                    }
                    break;
                }
            }
        }
         
    }
    return 0;
}