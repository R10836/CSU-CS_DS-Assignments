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
        int a[n],b[n],c[n];
        int j=0,k=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d",&a[i]);
            
            if(a[i]%2==0)
            {
                b[j]=a[i];
                j++;
            }
            else
            {
                c[k]=a[i];
                k++;
            }
       
        }

        quickSort(b,0,j-1);
        quickSort(c,0,k-1);

                 for(int i=0; i<=k-1; i++)
        {
            if(i==k-1)
            {
                printf("%d\n",c[i]);
            }
            if(i!=k-1)
            printf("%d ",c[i]);
        }


         for(int i=0; i<=j-1; i++)
        {
            if(i==j-1)
            {
                printf("%d\n\n",b[i]);
            }
            if(i!=j-1)
            printf("%d ",b[i]);
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