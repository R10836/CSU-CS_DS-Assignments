#include<stdio.h>

void quickSort(int *p, int left, int right);

struct inf
{
    char a[3];
    float avg;
}singer[999],t;

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        int x[5];
        for(int i=0; i<n; i++)
        {
            scanf(" %c%c%c %d %d %d %d %d",
            &singer[i].a[0],&singer[i].a[1],&singer[i].a[2],&x[0],&x[1],&x[2],&x[3],&x[4]);
            quickSort(x,0,4);
            singer[i].avg=(x[1]+x[2]+x[3])/3.0;//为什么/3就不能出小数了？
        }

        for(int i=0; i<n; i++)
        {
            for(int j=i+1; j<n+1; j++)
            {
                //注意如果某些选手的平均分成绩相同，则根据其编号，从小到大排序。
                if(singer[i].avg == singer[j].avg && (singer[i].a[0]*100+singer[i].a[1]*10+singer[i].a[2]) > (singer[j].a[0]*100+singer[j].a[1]*10+singer[j].a[2]))
                {
                    t=singer[j];
                    singer[j]=singer[i];
                    singer[i]=t;
                }
                if(singer[i].avg < singer[j].avg)
                {
                    t=singer[j];
                    singer[j]=singer[i];
                    singer[i]=t;
                }
            }
        }

        for(int i=0; i<n; i++)
        {
            printf("%c%c%c %5.2f\n",singer[i].a[0],singer[i].a[1],singer[i].a[2],singer[i].avg);
        }
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
问题 K: 20级期末机试1-评委打分（10分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
中南CC君近期组织中南大学大学生歌唱比赛，准备邀请五位评委根据参赛选手的表现打分。选手得分规则：去掉一个最高分和一个最低分，然后计算平均得分。他需要设计一个程序，能根据每位选手的平均分从高到低进行排序。你能帮帮他吗？
输入
多组样例。每组测试样例的第一行n，表示有n个参赛选手，n<1000；
下面的n行：每行包括参赛选手的编号（由数字组成的长度为3的字符串），及5位评委给的分数（整型），中间由空格分开。
输出
根据选手的平均分，从高到低的顺序依次输出每个选手的编号和平均分（四舍五入，保留两位小数）。注意如果某些选手的平均分成绩相同，则根据其编号，从小到大排序。
样例输入 Copy
5
001 98 95 82 85 90
002 76 87 90 90 88
003 90 92 97 95 93
004 97 88 86 90 92
010 99 98 97 96 96
样例输出 Copy
010 97.00
003 93.33
001 90.00
004 90.00
002 88.33
*/