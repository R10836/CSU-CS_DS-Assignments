#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define N 510

int n, m;         // 节点数和边数
int g[N][N];      // 邻接矩阵表示图的连接关系
bool vis[N];      // 记录节点是否被访问过

// 深度优先搜索函数
void dfs(int x) {
    char s = 'A' + x - 1;  // 将节点编号转换为对应的字母表示
    printf("%c ", s);      // 输出当前节点的字母表示
    vis[x] = 1;            // 标记当前节点为已访问
    for (int j = 1; j <= n; j++) {
        if (g[x][j] && vis[j] != 1) {
            dfs(j);        // 递归调用dfs函数继续遍历与当前节点相邻且未访问过的节点
        }
    }
}

int main() {
    int a, b, c;
    char s1, s2, s3;
    scanf("%d%d", &n, &m);  // 输入节点数和边数
    for (int i = 1; i <= m; i++) {
        scanf(" %c %c", &s1, &s2);      // 输入边的两个节点
        a = s1 - 'A' + 1;               // 将节点的字母表示转换为对应的编号
        b = s2 - 'A' + 1;
        g[a][b] = g[b][a] = 1;          // 在邻接矩阵中标记边的存在
    }
    scanf(" %c", &s3);                  // 输入遍历起点的节点字母
    c = s3 - 'A' + 1;                   // 将起点字母转换为编号
    dfs(c);                             // 调用深度优先搜索函数进行遍历
    return 0;
}
//时间复杂度为 O(n^2)，空间复杂度为 O(n)。