#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

void quickSort(int *p, int left, int right);

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        int a[n];
        
        for(int i=0; i<n; i++)
        {
            scanf("%d",&a[i]);
        }
        quickSort(a,0,n-1);
        int sum=0;
        if(n==1)
        {
            printf("Yes\n");
        }
        else
        {
        for(int i=1; i<n; i++)
        {
            sum+=a[i-1];
            if(a[i]<=sum)
            {
                printf("No\n");
                break;
            }
            if(i==n-1)
            {
                printf("Yes\n");
            }
        }
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