#include<stdio.h>//全程自做，用时30分钟

struct csu
{
    int m;
    int d;
    int y;
}date[99],t;//排序换位置时要找个暂存的“相同的容器”t

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
    {
        scanf("%d/%d/%d",&date[i].m,&date[i].d,&date[i].y);
    }
        for(int i=0; i<n-1; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                if(date[i].y != date[j].y)
                {
                    if(date[i].y > date[j].y)
                    {
                        t=date[i];
                        date[i]=date[j];
                        date[j]=t;
                        //若break放在此处，则无法跳出for
                    }
                    break;//放在这里，可跳出for。深究break的用法。即类似于swich里的break
                }
                if(date[i].m != date[j].m)
                {
                    if(date[i].m > date[j].m)
                    {
                        t=date[i];
                        date[i]=date[j];
                        date[j]=t;
                    }
                    break;
                }
                if(date[i].d != date[j].d)
                {
                    if(date[i].d > date[j].d)
                    {
                        t=date[i];
                        date[i]=date[j];
                        date[j]=t;
                    }
                    //最后一个，所以break可有可无
                }
            }
        }
        for(int i=0; i<n; i++)
        {
            if(date[i].m<10)//消除int型输出前面的0会消失的现象
            {
                printf("0%d/%d/%d\n",date[i].m,date[i].d,date[i].y);
                continue;//如果这里是break，那么整个for都跳出去了，要想一次打印一个日期，还得用continue
            }
            if(date[i].d<10)
            {
                printf("%d/0%d/%d\n",date[i].m,date[i].d,date[i].y);
                continue;
            }
            printf("%d/%d/%d\n",date[i].m,date[i].d,date[i].y);
        }
    return 0;
}

/*
问题 F: 22-结构体-2-日期排序
[命题人 : 外部导入]
时间限制 : 1.000 sec  内存限制 : 128 MB

题目描述
老师给了小南一些日期，日期格式为：MM/DD/YYYY。要求小南编程将其按日期大小排列，你能帮他完成吗？




输入
单样例。输入的第一行是一个整数n（0<n<100)，表示要排序日期的个数。
接下来的n行，每行输入一个日期，格式为MM/DD/YYYY。
输出
从小到大输出排序后的日期。
样例输入 Copy
3
02/21/2003
11/12/1999
10/22/2003
样例输出 Copy
11/12/1999
02/21/2003
10/22/2003
提示
也可以用链表实现。
*/