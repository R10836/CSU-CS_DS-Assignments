#include<stdio.h>//栽在了没看清题目要求上，考试时可以用结构体做，灵活解题工具

void quickSort(long *p, int left, int right);

int main()
{
    int n;
    scanf("%d",&n);
    long a[200000];//写成a[n]也能过。要注意函数里面的*p类型也得随数组类型而变
    for(int i=0; i<n; i++)
    {
        scanf("%lld",&a[i]);
    }

    quickSort(a,0,n-1);

    for(int i=0; i<n; i++)
    {
        if(a[i] != 0)
        {
            int sum=1;
            for(int j=i+1; j<n; j++)
            {
                if(a[i] == a[j])
                {
                    sum++;
                    a[j]=0;//因题上说a[i]的取值范围里面没有0，所以巧妙使用0作为标记，类比flag法
                }
            }
            printf("%lld %d\n",a[i],sum);
        }
    }
    return 0;
}

void quickSort(long *p, int left, int right)//快速排序算法对数列从小到大排
{
    if (left >= right)
        return;
    long pivot = p[left];
    int i = left, j = right;
    while (i < j)
    {
        while (i < j && p[j] >= pivot)
            j--;
        p[i] = p[j];
        while (i < j && p[i] < pivot)
            i++;
        p[j] = p[i];
    }
    p[i] = pivot;
    quickSort(p, left, i-1);
    quickSort(p, i+1, right);
}

/*
问题 C: 22-数组-3-统计数字
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 125 MB

题目描述
小南跟着导师进行科研调查，得到了n个自然数（1≤n≤200000），每个数均不超过1500000000（1.5*109），即long型。已知不相同的数不超过10000个，现在需要统计这些自然数各自出现的次数，并按照自然数从小到大的顺序输出统计结果。你能帮他编程实现吗？ 


输入
单样例。每个测试文件只包含一组测试数据：
第一行是整数n，表示自然数的个数；
第2~n+1行，每行一个自然数。


 


输出
输出包含m行（m为n个自然数中不相同数的个数），按照自然数从小到大的顺序输出。每行输出两个整数，分别是自然数和该数出现的次数，其间用一个空格隔开。


样例输入 Copy
8
2
4
2
4
5
100
2
100
样例输出 Copy
2 3
4 2
5 1
100 2
提示
也可以用结构体处理。
*/