#include<stdio.h>//结构体大题

struct inf
{
    int no;
    int sum;
    int math;
    int eng;
    int c;
}stu[1000],t;

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0; i<n; i++)
        {
            scanf("%d %d %d %d",
            &stu[i].no, &stu[i].math, &stu[i].eng, &stu[i].c);
            stu[i].sum = stu[i].math + stu[i].eng + stu[i].c;
        }
        for(int i=0; i<n-1; i++)//整了半大天原来所在了排序算法写错！！！！
        {
            for(int j=i+1; j<n; j++)
            {
                if(stu[i].sum < stu[j].sum)
                {
                    t=stu[j];//一定一定要注意换的是整个结构而不是结构里的一项内容
                    stu[j]=stu[i];
                    stu[i]=t;
                }
//事实证明可以把<和=放一个循环里判断，而不用像我一样再开个循环
                // if(stu[i].sum == stu[j].sum)
                // {
                //     if(stu[i].no > stu[j].no)
                //     {
                //         t=stu[j];
                //         stu[j]=stu[i];
                //         stu[i]=t;
                //     }
                // }
            }
        }
        for(int i=0; i<n; i++)
        {
            for(int j=i+1; j<n+1; j++)
            {
                if(stu[i].sum == stu[j].sum)
                {
                    if(stu[i].no > stu[j].no)
                    {
                        t=stu[j];
                        stu[j]=stu[i];
                        stu[i]=t;
                    }
                }
            }
        }
        printf("BEST\n");
        for(int i=0; i<n; i++)
        {
            if(stu[i].sum == stu[0].sum)//妙
            {
                printf("%d %d %d %d %d\n",
                stu[i].no, stu[i].sum, stu[i].math, stu[i].eng, stu[i].c);
            }
        }
        printf("WORST\n");
        for(int i=0; i<n; i++)
        {
            if(stu[i].sum == stu[n-1].sum)//妙
            {
                printf("%d %d %d %d %d\n",
                stu[i].no, stu[i].sum, stu[i].math, stu[i].eng, stu[i].c);
            }
        }
        printf("\n");
    }
    return 0;
}

/*
问题 AJ: 21级补考-考试测评（10分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
小南所在的专业进行了一次摸底考试，考试科目包括数学、英语和C语言三门。考试完后，他想知道，总分成绩最高的和最低的同学的信息，按照学号、总分、数学、英语和C语言的顺序给出。如果有多个最高分和最低分，要求全部输出，按学号有小到大排列。你能帮他实现吗？
输入
多组样例测试，每组样例的第一行为一个正整数n（1≤n≤1000），代表专业有n个同学。
接下来的n行对应n个同学的相关信息。每一行包含4个整数，分别代表该生的学号（4位整数）和数学、英语、C语言三门科目对应的分数g（0≤g≤100）。
输出
每个样例先输出"BEST"，再输出总分最高的学生信息，然后输出"WORST"，再输出总分最低的学生信息。每个学生的信息各占一行，按照学号、总分、数学、英语和C语言的顺序输出。注意如果有相同的最高分或最低分，则根据学号，从小到大排序全部输出。
每个测试样例的输出之间空一行，详情见样例 。
样例输入 Copy
4
1001 80 70 60
1002 100 100 100
2001 100 30 50
2002 70 80 66
5
1001 80 90 100
1002 100 90 90
2001 90 90 100
2002 88 89 92
2003 60 70 80
样例输出 Copy
BEST
1002 300 100 100 100
WORST
2001 180 100 30 50

BEST
1002 280 100 90 90
2001 280 90 90 100
WORST
2003 210 60 70 80
*/