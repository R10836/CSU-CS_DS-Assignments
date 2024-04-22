#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define N 510
#define INF 0x3f3f3f3f

int n, m;
int g[N][N]; // 图的邻接矩阵
int dist[N]; // 存储每个节点到最小生成树的最短距离
bool st[N]; // 标记节点是否已经加入最小生成树

void prim() {
    char s1, s2;
    memset(dist, 0x3f, sizeof dist); // 初始化距离数组为无穷大
    for (int i = 0; i < n; i++) {
        int t = -1;
        for (int j = 1; j <= n; j++) {
            if (!st[j] && (t == -1 || dist[t] > dist[j])) {
                t = j; // 找到距离最小的节点
            }
        }
        if (i && dist[t] == INF) {
            return; // 如果存在无法连通的节点，说明图不连通，返回
        } else if (i) {
            for (int j = 1; j <= n; j++) {
                if (dist[t] == g[t][j]) {
                    s1 = 'A' + t - 1;
                    s2 = 'A' + j - 1;
                    printf("%c %c %d\n", s2, s1, g[t][j]); // 输出边的信息
                    break;
                }
            }
        }
        st[t] = true; // 将节点加入最小生成树
        for (int j = 1; j <= n; j++) {
            dist[j] = (dist[j] < g[t][j]) ? dist[j] : g[t][j]; // 更新最短距离
        }
    }
}

int main() {
    int a, b, c;
    char s1, s2;
    scanf("%d%d", &n, &m); // 读取节点数和边数
    memset(g, 0x3f, sizeof g); // 初始化邻接矩阵，表示无穷大距离
    while (m--) {
        scanf(" %c %c %d", &s1, &s2, &c); // 读取边的信息
        a = s1 - 'A' + 1; // 将节点转换为对应的索引
        b = s2 - 'A' + 1;
        g[a][b] = g[b][a] = (g[a][b] < c) ? g[a][b] : c; // 更新边的权重
    }
    
    prim(); // 执行Prim算法生成最小生成树
    
    return 0;
}
//该算法的时间复杂度为 O(n^2)
//空间复杂度为 O(n^2)