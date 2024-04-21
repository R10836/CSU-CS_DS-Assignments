#include<stdio.h>
  
struct csu
{
    char name[11];
    int y;
    int s;
    int w;
    int sum;
}stu[101],t;
  
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0; i<n; i++)
        {
            scanf("%s %d %d %d",
            stu[i].name, &stu[i].y, &stu[i].s, &stu[i].w);
            stu[i].sum = stu[i].y + stu[i].s + stu[i].w;
        }
        //
        for(int i=0; i<n-1; i++)//他妈了个逼栽在了排序算法上！！！！
        {
            for(int j=i+1; j<n; j++)
            {
                if(stu[i].sum < stu[j].sum)
                {
                    t=stu[i];
                    stu[i]=stu[j];
                    stu[j]=t;
                }
                if(stu[i].sum == stu[j].sum)
                {
                    for(int k=0; ;k++)
                    {
                        if(stu[i].name[k] > stu[j].name[k])
                        {
                            t=stu[i];
                            stu[i]=stu[j];
                            stu[j]=t;
                            break;
                        }
                        else if(stu[i].name[k] < stu[j].name[k])
                        {
                            break;
                        }
                    }
                }
            }
        }
        for(int i=0; i<3; i++)
        {
            printf("%s %d\n", stu[i].name, stu[i].sum);
        }
        printf("\n");
        //
        for(int i=0; i<n-1; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                if(stu[i].y < stu[j].y)
                {
                    t=stu[i];
                    stu[i]=stu[j];
                    stu[j]=t;
                }
                if(stu[i].y == stu[j].y)
                {
                    for(int k=0; ;k++)
                    {
                        if(stu[i].name[k] > stu[j].name[k])
                        {
                            t=stu[i];
                            stu[i]=stu[j];
                            stu[j]=t;
                            break;
                        }
                        else if(stu[i].name[k] < stu[j].name[k])
                        {
                            break;
                        }
                    }
                }
            }
        }
        for(int i=0; i<3; i++)
        {
            printf("%s %d\n", stu[i].name, stu[i].y);
        }
        printf("\n");
        //
        for(int i=0; i<n-1; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                if(stu[i].s < stu[j].s)
                {
                    t=stu[i];
                    stu[i]=stu[j];
                    stu[j]=t;
                }
                if(stu[i].s == stu[j].s)
                {
                    for(int k=0; ;k++)
                    {
                        if(stu[i].name[k] > stu[j].name[k])
                        {
                            t=stu[i];
                            stu[i]=stu[j];
                            stu[j]=t;
                            break;
                        }
                        else if(stu[i].name[k] < stu[j].name[k])
                        {
                            break;
                        }
                    }
                }
            }
        }
        for(int i=0; i<3; i++)
        {
            printf("%s %d\n", stu[i].name, stu[i].s);
        }
        printf("\n");
        //
        for(int i=0; i<n-1; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                if(stu[i].w < stu[j].w)
                {
                    t=stu[i];
                    stu[i]=stu[j];
                    stu[j]=t;
                }
                if(stu[i].w == stu[j].w)
                {
                    for(int k=0; ;k++)
                    {
                        if(stu[i].name[k] > stu[j].name[k])
                        {
                            t=stu[i];
                            stu[i]=stu[j];
                            stu[j]=t;
                            break;
                        }
                        else if(stu[i].name[k] < stu[j].name[k])
                        {
                            break;
                        }
                    }
                }
            }
        }
        for(int i=0; i<3; i++)
        {
            printf("%s %d\n", stu[i].name, stu[i].w);
        }
        printf("\n");
    }
    return 0;
}

/*
问题 O: 20级期末机试2-光荣榜（10分）
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
中南CC君所在的班级进行了一次摸底考试，考试科目包括语文、数学、英语共三门。
中南CC君的老师汇总了成绩后列出了成绩单，其中包括每名同学的姓名和三科（语文、数学、英语）的成绩，及三科成绩的总分。现在老师希望表扬一下每门课程考试得分前三名和总分前三名的同学，同分数的情况下，名字字典序更小的排前面。
请你帮助老师写一个程序，快速完成这件事情吧。
输入
多组样例测试，每组样例的第一行为一个正整数n（3≤n≤100），代表n个同学。
接下来的n行对应n个同学的相关信息。每一行包含同学的名字s（1≤s≤10）和三个整数，三个整数分别代表的是该生语文、数学、英语三门科目对应的分数g（0≤g≤100）。

输出
输出每门考试的前三名的名字，和相应的分数。每个学生的信息各占一行，每科按换行隔开，按照总分，语文，数学，英语的顺序输出。
每个测试样例的输出之间空一行，详情见样例 。
样例输入 Copy
4
alice 80 70 60
bob 99 87 55
eric 100 30 99
lily 70 80 66
5
aaa 80 90 100
bbb 87 99 63
ccc 45 65 76
ddd 88 89 92
eee 99 87 95
样例输出 Copy
bob 241
eric 229
lily 216

eric 100
bob 99
alice 80

bob 87
lily 80
alice 70

eric 99
lily 66
alice 60

eee 281
aaa 270
ddd 269

eee 99
ddd 88
bbb 87

bbb 99
aaa 90
ddd 89

aaa 100
eee 95
ddd 92
*/