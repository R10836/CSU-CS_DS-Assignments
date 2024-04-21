#include<stdio.h>
#include<math.h>
#include<string.h>
//moon and stars sun things these like you

int gcd(int a,int b);

struct cu
{
    char wo[9999];
}word[9999];

int main()
{
    char s[9999];
    while(gets(s)!=NULL)
    {
        char  big='A';
        char sml='a';
        int num=1;
        int len=strlen(s);
        int m=0;
        for(int i=len-1; i>=0; i--)
        {
            if(s[i]==' ')
            {
                for(int j=0; s[i+1+j]!=' '&&j<5000;j++)
                {
                    word[m].wo[j]=s[i+1+j];
                }
                m++;
            }
            if(i==0)
            {
                for(int j=0; m<5000;j++)
                {
                    word[m].wo[j]=s[j];
                    if(s[j]==' ')
                    {
                        break;
                    }
                }
                m++;
            }
        }
        for(int i=0; i<m; i++)
        {
            printf("%s",word[i].wo);
            if(i!=m-1)
            printf(" ");
            if(i==m-1)
            printf("\n");
        }
        int n=gcd(len,m);
        for(int i=1; i<n-1; i++)
        {
            for(int j=0; j<n-1-i; j++)
            {
                printf(" ");
            }
            if(i==0)
            {
                for(int j=0; j<n; j++)
                {
                    printf("*");
                }
                printf("\n");
            }
            else
            {
                printf("*");
                for(int k=0; k<n-2; k++)
                {
                    if(big>'Z')
                    {
                        big-=26;
                    }
                    printf("%c",big);
                    big++;
                }
                printf("*");
                for(int k=0; k<i-1 ;k++)
                {
                    if(num>9)
                    {
                        num-=9;
                    }
                    printf("%d",num);
                    num++;
                }
                printf("*\n");

            }

        }
        for(int u=0; u<n-1; u++)
        {
            if(u==0)
            {
                for(int ii=0; ii<n;ii++)
                {
                    printf("*");
                }
                    for(int ii=0; ii<n-2;ii++)
                    {
                        if(num>9)
                    {
                        num-=9;
                    }
                    printf("%d",num);
                    num++;
                    }
                printf("*\n");
            }
            else
            {
                printf("*");
                for(int f=0; f<n-2; f++)
                {
                if(sml>'z')
                    {
                        sml-=26;
                    }
                    printf("%c",sml);
                    sml++;
                }
                printf("*");
                                for(int k=0; k<n-u-3;k++)
                {
                    if(num>9)
                    {
                        num-=9;
                    }
                    printf("%d",num);
                    num++;
                }
                printf("*\n");
            }
        }
        for(int op=0 ;op<n; op++)
        {
            printf("*");
        }
        printf("\n");

    }
    printf("\n");
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
