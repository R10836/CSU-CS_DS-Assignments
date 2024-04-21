/*
问题 C: 22-数组-1-杨辉三角
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
杨辉三角，其特点是两个腰上的数字都为1，其它位置上的数字是其上一行中与之相邻的两个整数之和。 
如下图，就是一个6层的杨辉三角
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
1 5 10 10 5 1 
输入
多样例。每组测试样例输入只包含一个正整数n（1≤n≤50），表示将要输出的杨辉三角的层数。
输出
对应于每一个输入，输出相应层数的杨辉三角，每一层的整数之间用一个空格隔开，每一个杨辉三角后面加一个空行。
样例输入 Copy
2
3
样例输出 Copy
1
1 1

1
1 1
1 2 1
*/

/*
#include<stdio.h>

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        long long int a[51][51];

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<=i; j++)
            {
                if(j==0 || j==i)
                {
                    a[i][j]=1;
                }
                else
                {
                    a[i][j]=a[i-1][j-1]+a[i-1][j];
                }
            }
        }

        for(int i=0; i<n; i++)
        {
            for(int j=0; j<=i; j++)
            {
                printf("%d",a[i][j]);
                if(j != i)
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
*/

/*网上解法有感，所以错就错在了int型上，以为杨辉51太大，int放不下
#include<stdio.h>
double jie(double n);
int main()
{
	double n;
	while (scanf("%lf", &n) != EOF)
    {
		double i;
		double j;
		for (i = 1; i <= n; i++)
        {
			for (j = 0; j < i; j++)
            {
				if (i==1&&j==0)
                {
					printf("%d\n",1);
				}
				else if (i != 1 && j == 0)
                {
					printf("%d ",1);
				}
				else if (i != 1 && j == i - 1)
                {
					printf("%d\n",1);
				}
				else {
					printf("%.0f ", jie(i - 1) / (jie(j) * jie(i - 1 - j)));
				}
			}
		}
		printf("\n");
	}
	

}
double jie(double n) {
	if (n <= 1)
    {
		return 1;
	}
	else
    {
		return n * jie(n - 1);
	}
}
*/

//我的改版：（原来败在了溢出上）且一定要记得long long是%lld

#include<stdio.h>
 
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        long long int a[51][51];
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<=i; j++)
            {
                if(j==0 || j==i)
                {
                    a[i][j]=1;
                }
                else
                {
                    a[i][j]=a[i-1][j-1]+a[i-1][j];
                }
            }
        }
 
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<i+1; j++)
            {
                printf("%lld",a[i][j]);
                if(j != i)
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}