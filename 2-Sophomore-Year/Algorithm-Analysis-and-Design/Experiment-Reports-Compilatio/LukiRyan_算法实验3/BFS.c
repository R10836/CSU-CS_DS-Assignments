#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define N 510

int n, m;               // 节点数和边数
int g[N][N];            // 邻接矩阵表示图的连接关系
bool vis[N];            // 记录节点是否被访问过
int queue[N], front = 0, rear = 0;  // 队列用于广度优先搜索

void bfs() {
    while (front < rear) {          // 队列不为空时进行循环
        int x = queue[front++];     // 取出队首节点
        vis[x] = 1;                 // 标记当前节点为已访问
        char s = 'A' + x - 1;       // 将节点编号转换为对应的字母表示
        printf("%c ", s);           // 输出当前节点的字母表示
        for (int j = 1; j <= n; j++) {
            if (vis[j] != 1 && g[x][j]) {  // 若节点未被访问且与当前节点相邻
                queue[rear++] = j;         // 将节点入队
                vis[j] = 1;                 // 标记节点为已访问
            }
        }
    }
}

int main() {
    int a, b, c;
    char s1, s2, s3;
    scanf("%d%d", &n, &m);              // 输入节点数和边数
    for (int i = 1; i <= m; i++) {
        scanf(" %c %c", &s1, &s2);      // 输入边的两个节点
        a = s1 - 'A' + 1;               // 将节点的字母表示转换为对应的编号
        b = s2 - 'A' + 1;
        g[a][b] = g[b][a] = 1;          // 在邻接矩阵中标记边的存在
    }
    scanf(" %c", &s3);                  // 输入遍历起点的节点字母
    c = s3 - 'A' + 1;                   // 将起点字母转换为编号
    queue[rear++] = c;                  // 将起点节点入队
    bfs();                              // 调用广度优先搜索函数进行遍历
    return 0;
}
//时间复杂度为O(n+m)，空间复杂度为O(n)