#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
float sum(float arr[], int a, int b);

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        float a[n];
        for(int i=0; i<n; i++)
        {
            scanf("%f",&a[i]);
            if(i>=1)
            {

          
            float now=sum(a,0,i-1);
            if(now>=10.0 && now<15.0)
            {
                a[i]=a[i]*0.8;
            }
            if(now>=15.0 && now<40.0)
            {
                a[i]*=0.5;
            }

              }
        }


        float all=sum(a,0,n-1);
        if(all>=100.0)
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



//求数组闭区间[a,b]之间所有数的和 
float sum(float arr[], int a, int b)
{
    float sum=0;
    for(int i=a; i<=b; i++)
    {
        sum+=arr[i];
    }
    return sum;
}