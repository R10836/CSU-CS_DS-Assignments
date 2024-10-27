//
// Created by Shawn33712 on 24-8-29.
//

/*

代码
测试用例
测试结果
测试结果
1926. 迷宫中离入口最近的出口
中等
相关标签
相关企业
提示
给你一个 m x n 的迷宫矩阵 maze （下标从 0 开始），矩阵中有空格子（用 '.' 表示）和墙（用 '+' 表示）。同时给你迷宫的入口 entrance ，用 entrance = [entrancerow, entrancecol] 表示你一开始所在格子的行和列。

每一步操作，你可以往 上，下，左 或者 右 移动一个格子。你不能进入墙所在的格子，你也不能离开迷宫。你的目标是找到离 entrance 最近 的出口。出口 的含义是 maze 边界 上的 空格子。entrance 格子 不算 出口。

请你返回从 entrance 到最近出口的最短路径的 步数 ，如果不存在这样的路径，请你返回 -1 。



示例 1：


输入：maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance = [1,2]
输出：1
解释：总共有 3 个出口，分别位于 (1,0)，(0,2) 和 (2,3) 。
一开始，你在入口格子 (1,2) 处。
- 你可以往左移动 2 步到达 (1,0) 。
- 你可以往上移动 1 步到达 (0,2) 。
从入口处没法到达 (2,3) 。
所以，最近的出口是 (0,2) ，距离为 1 步。
示例 2：


输入：maze = [["+","+","+"],[".",".","."],["+","+","+"]], entrance = [1,0]
输出：2
解释：迷宫中只有 1 个出口，在 (1,2) 处。
(1,0) 不算出口，因为它是入口格子。
初始时，你在入口与格子 (1,0) 处。
- 你可以往右移动 2 步到达 (1,2) 处。
所以，最近的出口为 (1,2) ，距离为 2 步。
示例 3：


输入：maze = [[".","+"]], entrance = [0,0]
输出：-1
解释：这个迷宫中没有出口。


提示：

maze.length == m
maze[i].length == n
1 <= m, n <= 100
maze[i][j] 要么是 '.' ，要么是 '+' 。
entrance.length == 2
0 <= entrancerow < m
0 <= entrancecol < n
entrance 一定是空格子。
*/

#include "iostream"
#include "vector"
#include "queue"

using namespace std;


class Solution {
public:
    int step = 0;

    bool found = false;

    int dir[4][2] = {
        {1, 0},  // 上
        {-1, 0}, // 下
        {0, -1}, // 左
        {0, 1}   // 右
    };

    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        // 准备
        int y = entrance[0];
        int x = entrance[1];

        // 正文
        bfs(maze, y, x);

        // 返回
        if (found) {
            return step;
        } else {
            return -1;
        }
    }

    void bfs(vector<vector<char>>& maze, int y, int x) {
        // 准备工作
        int rows = maze.size();
        int cols = maze[0].size();

        queue<pair<int, int>> q;

        q.push({y, x});  // 处理初试节点
        maze[y][x] = '+';  // 处理初试节点

        // 队列
        while(!q.empty()) {
            int size = q.size();  // 当前层的节点数量

            for (int i = 0; i < size; i++) {  // 遍历当前层的所有节点
                int y1 = q.front().first;
                int x1 = q.front().second;
                q.pop();

                for (int j = 0; j < 4; j++) {  // 遍历四个方向
                    int y2 = y1 + dir[j][0];
                    int x2 = x1 + dir[j][1];

                    if (y2 == -1 || y2 == rows || x2 == -1 || x2 == cols) {
                        if (x1 == x && y1 == y) {  // 入口即出口不算
                            continue;
                        }
                        found = true;
                        return;
                    }

                    if (maze[y2][x2] == '+') {
                        continue;
                    }

                    q.push({y2, x2});  // 处理节点
                    maze[y2][x2] = '+';  // 处理节点
                }
            }
            step++;  // 每遍历一层，步数增加
        }
    }
};


int main() {
    Solution solution;

    vector<vector<char>> maze = {
            {'+','+','+','+','+'},
            {'+','.','.','.','+'},
            {'+','.','+','.','+'},
            {'.','.','.','.','+'},
            {'+','+','.','+','.'},
    };
    vector<int> entrance = {3,0};
    cout << solution.nearestExit(maze, entrance) << endl;

    return 0;
}

//int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1}; // 表示四个方向
// // grid 是地图，也就是一个二维数组
// // visited标记访问过的节点，不要重复访问
// // x,y 表示开始搜索节点的下标
//void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
//    queue<pair<int, int>> que; // 定义队列
//    que.push({x, y}); // 起始节点加入队列
//    visited[x][y] = true; // 只要加入队列，立刻标记为访问过的节点
//    while(!que.empty()) { // 开始遍历队列里的元素
//        pair<int ,int> cur = que.front(); que.pop(); // 从队列取元素
//        int curx = cur.first;
//        int cury = cur.second; // 当前节点坐标
//        for (int i = 0; i < 4; i++) { // 开始想当前节点的四个方向左右上下去遍历
//            int nextx = curx + dir[i][0];
//            int nexty = cury + dir[i][1]; // 获取周边四个方向的坐标
//            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) continue;  // 坐标越界了，直接跳过
//            if (!visited[nextx][nexty]) { // 如果节点没被访问过
//                que.push({nextx, nexty});  // 队列添加该节点为下一轮要遍历的节点
//                visited[nextx][nexty] = true; // 只要加入队列立刻标记，避免重复访问
//            }
//        }
//    }
//
//}
