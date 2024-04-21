#include<stdio.h>

int find(int a[],int sz,int x);

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        int a[1000];
        for(int i=0; i<n; i++)
            {
                scanf("%d",&a[i]);
            }
        int x;
        scanf("%d",&x);

        int xiabiao=find(a,n,x);

        printf("%d\n",xiabiao);
    }
    return 0;
}

int find(int a[],int sz,int x)
{//在数组a中搜数x。其中sz是数组的大小，一定要在调此函数前算出
    int key;
    for(int i=0; i<sz; i++)
    {
        if(x==a[i])
        {
            key=i+1;
            break;
        }
        else
        {
            if(i==sz-1)
            {
                key=-1;
                break;
            }
        }
    }
    return key;
}//key是数x的(下标+1)人眼中的第几个，若没搜到，则输出-1


/*
若题目改问：
输出数组中所有匹配到的元素的下标，则：

#include<stdio.h>

void find(int a[],int sz,int x);

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        int a[1000];
        for(int i=0; i<n; i++)
            {
                scanf("%d",&a[i]);
            }
        int x;
        scanf("%d",&x);

        find(a,n,x);
    }
    return 0;
}


//在元素个数为sz的数组a中搜元素x，并打印元素x的下标key。
//其中sz是数组的大小，一定要在调此函数前算出

void find(int a[],int sz,int x)
{
    int key;
    int flag=0;
    for(int i=0; i<sz; i++)
    {
        if(x==a[i])
        {
            key=i;
            flag=1;
            printf("%d ",key);
        }
        else
        {
            if(i==sz-1 && flag==0)
            {
                key=-1;
                printf("-1\n");
            }
            if(i==sz-1 && flag==1)
            {
                printf("\n");
            }
        }
    }
}//key是数x的(下标+1)人眼中的第几个，若没搜到，则输出-1
*/