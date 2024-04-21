//栽在了思维的不慎密 && 懒得动笔
#include<stdio.h>
#include<string.h>
#include<math.h>

void quickSort(int *p, int left, int right);

int main()
{
    char a[999];
    int b[999]={0};
    scanf("%s",a);//用gets(a)不让通过
    int k=0;
    for(int i=0; i<strlen(a); i++)
    {
        if(i>=1 && a[i]=='5')
        {
            int flag=0;
            for(int j=i-1,q=0; j>=0 && a[j]!='5'; j--,q++)
            {
                int x=a[j]-48;
                b[k]+=(x*pow(10,q));
                flag=1;
            }
            if(flag==1)
            {
                k++;
            }
        }
        if(i==strlen(a)-1 && a[i]!='5')
        {
            int flag=0;
            for(int j=i,q=0; j>=0 && a[j]!='5'; j--,q++)//此时最后一个数字要算进去
            {
                int x=a[j]-48;//巧妙的将'6'转变为6
                b[k]+=(x*pow(10,q));
                flag=1;
            }
            if(flag==1)
            {
                k++;
            }
        }
    }
    quickSort(b, 0, k-1);
    for(int i=0; i<k; i++)
    {
        printf("%d ",b[i]);
    }
    return 0;
}

//快速排序算法对数列从小到大排：(数组名-但要注意数组类型是否也是int, 数组第一个元素的下标, 数组最后一个元素的下标)
void quickSort(int *p, int left, int right)
{//(数组名-但要注意数组类型是否也是int, 数组第一个元素的下标, 数组最后一个元素的下标)
    if (left >= right)
        return;
    int pivot = p[left];
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
问题 E: 分割排序
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 32 MB

题目描述
输入一行数字，如果我们把这行数字中的‘5’都看成空格，那么就得到一行用空格分割的若干非负整数（可能有些整数以‘0’开头，这些头部的‘0’应该被忽略掉，除非这个整数就是由若干个‘0’组成的，这时这个整数就是0）。
你的任务是：对这些分割得到的整数，依从小到大的顺序排序输出。

输入
每组输入数据只有一行数字（数字之间没有空格），这行数字的长度不大于1000。  
输入数据保证：分割得到的非负整数不会大于100000000，输入数据不可能全由‘5’组成。

输出
输出分割得到的整数排序的结果，相邻的两个整数之间用一个空格分开，每组输出占一行。

样例输入 Copy
0051231232050775
样例输出 Copy
0 77 12312320
*/