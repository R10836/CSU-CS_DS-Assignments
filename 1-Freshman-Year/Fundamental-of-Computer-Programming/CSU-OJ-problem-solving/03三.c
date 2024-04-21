#include<stdio.h>


int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0; i<n+1; i++)
        {
            for(int j=0; j<n-i; j++)
            {
                printf(" ");
            }
            for(int j=0; j<2*i+1; j++)
            {
                printf("*");
            }
            printf("\n");
        }
        
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                printf(" ");
            }
            
            printf("*");

            printf("\n");
        }
    }
    return 0;
}