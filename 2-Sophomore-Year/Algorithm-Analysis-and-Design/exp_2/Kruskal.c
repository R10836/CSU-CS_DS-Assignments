#include<stdio.h>
#include<string.h> 
#include<stdlib.h> 
#define N 100010 
#define M 200010 
#define INF 0x3f3f3f3f

int p[N]; // 并查集数组，用于存储每个顶点的父节点
int n, m; // 顶点数和边数

struct Edge{ 
    int a, b, w; // 边的起始顶点、结束顶点和权重
};

Edge e[M]; // 边的数组，用于存储边的信息

// 比较函数，用于边的排序
int cmp(const void *a, const void *b){
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return x->w - y->w; 
}

// 并查集的查找操作
int find(int x){
    if(x != p[x])
        p[x] = find(p[x]); // 路径压缩
    return p[x]; 
}

// Kruskal算法实现
void kru(){
    char s1, s2; 
    qsort(e, m, sizeof(Edge), cmp); // 对边按权重进行排序

    for(int i = 1; i <= n; i++) 
        p[i] = i; // 初始化并查集数组，每个顶点自成一个连通分量

    int cnt = 0; // 计数器，记录已添加到最小生成树的边数

    for(int i = 0; i < m; i++){
        int a = e[i].a, b = e[i].b, w = e[i].w; // 当前遍历的边的起始顶点、结束顶点和权重

        a = find(a); // 查找顶点a的父节点
        b = find(b); // 查找顶点b的父节点

        if(a != b){ // 顶点a和b不属于同一个连通分量，不会形成环
            p[a] = b; // 将顶点a的父节点更新为顶点b的父节点，表示合并连通分量
            s1 = 'A' + a - 1; // 起始顶点转换为对应的字母表示
            s2 = 'A' + b - 1; // 结束顶点转换为对应的字母表示
            printf("%c %c %d\n", s1, s2, w); // 打印边的信息
            cnt++; // 边数加1
        }
    }
}

int main(){
    int a, b, c;
    char s1, s2; 
    scanf("%d %d", &n, &m); // 读取顶点数和边数

    for(int i = 0; i < m; i++){
        scanf(" %c %c %d", &s1, &s2, &c); // 读取每条边的起始顶点、结束顶点和权重
        a = s1 - 'A' + 1; // 起始顶点转换为对应的整数值
        b = s2 - 'A' + 1; // 结束顶点转换为对应的整数值
        e[i].a = a;
        e[i].b = b;
        e[i].w = c;
    } 

    kru(); // 执行Kruskal算法找到最小生成树

    return 0; 
}
//对边按照权值从小到大排序的时间复杂度为O(mlogm)，其中m为边的数量；
//初始化并查集的时间复杂度为O(n)，其中n为点的数量；
//遍历每条边的时间复杂度为O(m)，在并查集中查找每个点的父节点的时间复杂度为O(logn)，因此总时间复杂度为O(mlogn)；
//当输出的边数达到n-1时，停止遍历，因此最多需要遍历m条边；
//空间复杂度主要取决于数组e和并查集p的大小，因此为O(m+n)