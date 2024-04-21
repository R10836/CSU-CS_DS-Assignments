#include<stdio.h>
#include<math.h>

int gcd(int a,int b);

int main()
{
    int a,b,c,d;
    char fu;
    while(scanf("%d/%d%c%d/%d",&a,&b,&fu,&c,&d)!=EOF)
    {
        if(fu=='+')
        {
            int x=a*d+b*c;
            int y=b*d;
            int m=gcd(x,y);
            x/=m;
            y/=m;
            if(x==y)
            {
                printf("1\n");
            }
            else if(x>y)
            {
                int zh=x/y;
                x=x%y;
                if(x!=0)//栽在了这
                {
                    printf("%d+%d/%d\n",zh,x,y);
                }
                else
                {
                    printf("%d\n",zh);
                }
            }
            else
            {
                printf("%d/%d\n",x,y);
            }
        }
        else
        {
            int x=a*d-b*c;
            int y=b*d;
            if(x==0)
            {
                printf("0\n");
            }
            else if(x>0)
            {
                int m=gcd(x,y);
                x/=m;
                y/=m;
                if(x==y)
                {
                    printf("1\n");
                }
                else if(x>y)
                {
                    int zh=x/y;
                    x=x%y;
                    if(x!=0)
                    {
                        printf("%d+%d/%d\n",zh,x,y);
                    }
                    else
                    {
                        printf("%d\n",zh);
                    }
                }
                else
                {
                    printf("%d/%d\n",x,y);
                }
            }
            else
            {
                x=abs(x);
                int m=gcd(x,y);
                x/=m;
                y/=m;
                if(x==y)
                {
                    printf("-1\n");
                }
                else if(x>y)
                {
                    int zh=x/y;
                    x=x%y;
                    if(x!=0)
                    {
                        printf("-%d+%d/%d\n",zh+1,y-x,y);
                    }
                    else
                    {
                        printf("-%d\n",zh+1);
                    }
                }
                else
                {
                    printf("-%d/%d\n",x,y);
                }
            }
        }
    }
    return 0;
}

//翁恺辗转相除法求最大公约数
int gcd(int a,int b)
{
	int t;
	while(b!=0)
    {
		t=a%b;
		a=b;
		b=t;
	}
	return a;
}

/*
问题 J: 20级期末机试1-分数加减（20分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
中南CC君最害怕分数的减法运算，因为对输出结果有特别的要求。首先是要对分数化简，然后是假分数要写成一个整数+真分数的形式，更麻烦的是，当结果是负的假分数时，要求写成一个负整数+正的真分数的形式。你能帮帮他吗？
输入
多组样例。每行一个样例以a/b-c/d或a/b+c/d的形式输入（a,b,c,d都是小于10000的正整数）。
输出
对于每一个输入的样例，输出一个结果。注意对结果要化简。如果是整数就直接输出，不需要以分数形式输出，如果是真分数就直接以e/f的形式输出，如果假分数如5/3，则以1+2/3的形式输出，如果是-5/3，则以-2+1/3的形式输出。
样例输入 Copy
1/1-2/3
1/2+2/3
1/2-8/2
样例输出 Copy
1/3
1+1/6
-4+1/2
*/