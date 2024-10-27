#include <stdio.h>

// 快速排序函数
void quickSort(int arr[], int left, int right) {
    if (left < right) {
        int pivot = arr[left];  // 选择左边的元素作为枢纽元素
        int i = left, j = right;
        while (i < j) {
            // 从右边开始，找到第一个小于等于枢纽元素的元素
            while (i < j && arr[j] > pivot) {
                j--;
            }
            if (i < j) {
                arr[i++] = arr[j];  // 将找到的元素放到左边
            }
            // 从左边开始，找到第一个大于枢纽元素的元素
            while (i < j && arr[i] < pivot) {
                i++;
            }
            if (i < j) {
                arr[j--] = arr[i];  // 将找到的元素放到右边
            }
        }
        arr[i] = pivot;  // 将枢纽元素放到正确的位置
        // 递归调用，对枢纽元素左右两侧的子数组进行排序
        quickSort(arr, left, i - 1);
        quickSort(arr, i + 1, right);
    }
}

// 划分函数，用于快速排序中确定枢纽元素的位置
int partition(int arr[], int left, int right) {
    int pivot = arr[left];  // 选择左边的元素作为枢纽元素
    int i = left, j = right;
    while (i < j) {
        // 从右边开始，找到第一个小于等于枢纽元素的元素
        while (i < j && arr[j] > pivot) {
            j--;
        }
        if (i < j) {
            arr[i++] = arr[j];  // 将找到的元素放到左边
        }
        // 从左边开始，找到第一个大于枢纽元素的元素
        while (i < j && arr[i] < pivot) {
            i++;
        }
        if (i < j) {
            arr[j--] = arr[i];  // 将找到的元素放到右边
        }
    }
    arr[i] = pivot;  // 将枢纽元素放到正确的位置
    return i;
}

// 查找第k大的元素
int findKthLargest(int arr[], int left, int right, int k) {
    int index = partition(arr, left, right);  // 使用划分函数确定枢纽元素的位置
    if (index == k - 1) {
        return arr[index];  // 找到第k大的元素
    } else if (index < k - 1) {
        return findKthLargest(arr, index + 1, right, k);  // 在右侧递归查找第k大的元素
    } else {
        return findKthLargest(arr, left, index - 1, k);  // 在左侧递归查找第k大的元素
    }
}

int main() {
    int m, k;
    int a[100000];
    scanf("%d%d", &m, &k);  // 输入数组大小和k的值
    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);  // 输入数组元素
    }
    quickSort(a, 0, m - 1);  // 对数组进行快速排序,排好后再给findKthLargest
    int kthLargest = findKthLargest(a, 0, m - 1, m - k + 1);  // 查找第k大的元素
    printf("%d\n", kthLargest);  // 输出结果
    return 0;
}

//此代码中使用的是快速排序算法和查找第k大元素算法
//它们的时间复杂度分别为O(nlogn)和O(n)
//因此整个代码的时间复杂度为O(nlogn)
//其中，快速排序的平均时间复杂度为O(nlogn)，最差情况下为O(n^2)