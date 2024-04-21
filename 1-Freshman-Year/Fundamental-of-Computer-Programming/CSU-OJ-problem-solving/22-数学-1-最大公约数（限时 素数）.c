/* #include<stdio.h>

int this(int x);

int main()
{
    int k, a, b;
    while(scanf("%d",&k)!=EOF)
    {
        while(k--)
        {
            scanf("%d%d",&a,&b);
            printf("%d\n",this(b)-this(a-1));
        }
    }
    return 0;
}

// 很重要的思路就是某一个数（假设为o）除以3，那么得到的就是[1,o]这个区间的能被3整除的数的个数，同理，除以2也如此。但有些数，既能被2整除，又能被3整除，所以要减去。
int this(int x)
{
    int bei2,bei3,bei6;
    bei2=x/2;
    bei3=x/3;
    bei6=x/6;
    return x-(bei2+bei3-bei6);
}
//然而超时了，所以用以下：
*/


#include<stdio.h>
int main()
{
    int k,a,b,sum,a1,b1,c,d;
    scanf("%d",&k);
    while(k--)
    {
        scanf("%d%d",&a,&b);
        for(int i=a;;i++)
        {
            if(i%6==0)
            {
                a1=i;
                break;
            }
        }
        for(int i=b;;i--)
        {
            if(i%6==0)
            {
                b1=i;
                break;
            }
        }
        c=0;
        if(b1>=a1)
        {
            for(int i=a;i<=a1;i++)
            {
                if(i%6==1 || i%6==5)
                    c++;
            }
            for(int i=b1;i<=b;i++)
            {
                if(i%6==1 || i%6==5)
                    c++;
            }
            printf("%d\n",c+(b1-a1)/6*2);
        }
        if(a1>b1)
        {
            for(int i=a;i<=b;i++)
            {
                if(i%6==1 || i%6==5)
                    c++;
            }
            printf("%d\n",c);
        }
    }
}
/*
问题 G: 22-数学-1-最大公约数
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
如果d是能整除a和b的最大的数，则称d为a和b的最大公约数(Greatest Common Divisor)，记作gcd(a,b)。如果gcd(a,b)=1，我们就称a和b是互素的。
现给一个区间[a,b](1≤a≤b≤109)，求与6互素的数的个数。例如：区间[1,10],与6互素的数为1,5,7,所以一共是3个。
小南知道一个简单的方法就是对于每一个区间[a,b]，采用穷举的方法去判断区间内的每一个数是否与6互素，然后进行统计。但是这样的话有可能会超时哦，所以你需要利用一些数学基础想到优化的方法去帮助小南完成任务。
输入
多样例。样例的个数由第一行输入的一个整数k(k≤10000)确定。接下来的k行表示输入的k个样例，每个样例输入占一行,为两个用空格分开的正整数a和b，表示区间[a,b](1≤a≤b≤109)。
输出
对于每个样例输入，输出一个整数表示统计的结果，每个结果占一行，
样例输入 Copy
2
1 10
1 1000000000?
样例输出 Copy
3
333333333
提示
考虑计算区间[1~x]之间与6互素的整数个数的公式。
*/