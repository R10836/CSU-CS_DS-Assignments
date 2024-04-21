#include<stdio.h>
#include<string.h>

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        char you='a';
        for(int k=0; k<n; k++)
        {
            for(int i=0; i<n-1-k; i++)
            {
                printf(" ");
            }
            char you2=you;
            for(int i=0; i<k; i++)
            {
                printf("%c",you2);//printf里面不加& ！！！
                you2--;
            }
            printf("a");
            char you3='a'+1;//第二个错点，老问题：借用外循环的变量参与内循环时一定记得把外变量复制一个
            for(int i=0; i<k; i++)
            {
                printf("%c",you3);
                you3++;
            }
            you++;
            printf("\n");
        }
    }
    return 0;
}

/*
#include<stdio.h>
#include<string.h>

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        char you='a';
        for(int k=0; k<n; k++)
        {
            for(int i=0; i<n-1-k; i++)
            {
                printf(" ");
            }
            char you2=you;
            for(int i=0; i<k; i++)
            {
                printf("%c",you2);
                you2--;
            }
            printf("a");
            char you3='b';
            for(int i=0; i<k; i++)
            {
                printf("%c",you3);
                you3++;
            }
            you++;
            printf("\n");
        }
    }
    return 0;
}
*/