//看清题，才能做对题

#include<stdio.h>

int sum(int arr[], int a, int b);

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        int a[100];
        for(int i=0; i<n; i++)
        {
            scanf("%d",&a[i]);
        }
        
        if(n%2 != 0 && sum(a,0,n-1)%2 != 0)
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
    return 0;
}

//求闭区间[a,b]之间所有数的和 
int sum(int arr[], int a, int b)
{
    int sum=0;
    for(int i=a; i<=b; i++)
    {
        sum+=arr[i];
    }
    return sum;
}

/*
问题 AF: 21级补考-奇数序列（20分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
小南有很多长度不同的整数序列，他发现其中有些序列有一个共同的特点，就是序列中元素的个数是奇数，序列中所有元素的和也是奇数（0认为是偶数），于是他将其取名为奇数序列。现在有若干个长度为n（1≤n≤100）的序列，请你帮他判断是否是奇数序列。
输入
多组样例，每组样例包括两行输入。第一行包含一个正整数n(1≤n≤100)，第二行包含n个整数ai (-106≤ ai ≤ 106) 。
输出
对于每组输入样例，输出一个结果。如果序列满足奇数序列要求就输出"YES"，否则输出"NO"。每个输出占一行。
样例输入 Copy
3
-1 5 1
2
10 3
3
4 -30 10
5
3 9 9 3 5
样例输出 Copy
YES
NO
NO
YES
*/