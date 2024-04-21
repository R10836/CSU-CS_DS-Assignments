#include<stdio.h>
#include<math.h>
#include<string.h>
int main()
{
    int n,i,j,m,flag=1;//b[i]=x;while{i<500}if(prime(x)) {b[i++]=x} x++  
    int a[31][31];
    int b[10000]; 
    i=3;
    b[1]=2;
    b[2]=3;
    for(j=4;j<=10000;j++)
    {
        for(m=2;m<=sqrt(j);m++)
        {
            if(j%m==0)
            {
                flag=0;
                break;
            }
        }
        if(flag==1)
        {
            b[i]=j;
            i++;
        }
        flag=1;//找到所有素数
    }
    while((scanf("%d",&n))!=EOF)
    {
        a[1][1]=1;
        a[2][1]=1;
        a[2][2]=1;
        for(i=3;i<=n;i++)
        {
            for(j=1;j<=i;j++)
            {
                a[i][1]=1;
                a[i][j]=a[i-1][j-1]+a[i-1][j];
                a[i][i]=1;
            }
        }//杨辉三角
        int k=1;
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
            {
                if(i>=j)
                {
                    printf("%d ",a[i][j]);//开始打印
                }
                if(i<j)
                {
                    printf("%d ",b[k]);//else a[i][j]=b[k++]
                    k++;
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0; 
}