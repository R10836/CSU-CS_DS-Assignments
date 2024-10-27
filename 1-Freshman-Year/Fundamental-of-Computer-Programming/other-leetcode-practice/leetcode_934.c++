//
// Created by Shawn33712 on 24-10-16.
//

/*
934. 最短的桥
中等
相关标签
相关企业
给你一个大小为 n x n 的二元矩阵 grid ，其中 1 表示陆地，0 表示水域。

岛 是由四面相连的 1 形成的一个最大组，即不会与非组内的任何其他 1 相连。grid 中 恰好存在两座岛 。

你可以将任意数量的 0 变为 1 ，以使两座岛连接起来，变成 一座岛 。

返回必须翻转的 0 的最小数目。



示例 1：

输入：grid = [[0,1],[1,0]]
输出：1
示例 2：

输入：grid = [[0,1,0],[0,0,0],[0,0,1]]
输出：2
示例 3：

输入：grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
输出：1


提示：

n == grid.length == grid[i].length
2 <= n <= 100
grid[i][j] 为 0 或 1
grid 中恰有两个岛
*/

#include "iostream"
#include "vector"
#include "queue"

using namespace std;


class Solution {
public:
    queue<vector<int>> q;

    vector<vector<int>> dir = {
            {1,0},
            {-1,0},
            {0,-1},
            {0,1}
    };

    int shortestBridge(vector<vector<int>>& grid) {
        // 准备
        int lenY = grid.size();
        int lenX = grid[0].size();

        // 先找到第二个岛，并有别于第一个岛
        for (int i = 0; i < lenY; i++) {
            for (int j = 0; j < lenX; j++) {
                if (grid[i][j] == 1) {
                    infect(grid, lenY, lenX, i, j);
                    goto label;
                }
            }
        }
        label:

        // 第二个岛一圈一圈往外扩，并count，找到第一个岛为止
        int count = 0;
        while(!q.empty()) {
            int level = q.size();
            for (int l = 0; l < level; l++) {
                vector<int> now = q.front();
                q.pop(); // 记得用完即丢！！！
                int y = now[0];
                int x = now[1];

                for (int k = 0; k < 4; k++) {
                    int yo = y + dir[k][0];
                    int xo = x + dir[k][1];
                    if (xo < 0 || xo >= lenX) { continue;}
                    if (yo < 0 || yo >= lenY) { continue;}
                    if (grid[yo][xo] == 0) {
                        grid[yo][xo] = 2;
                        q.push({yo, xo});
                    } else if (grid[yo][xo] == 1) {
                        return count;
                    }
                }
                // printG(grid);
            }

            // printG(grid);
            count++;

            /*
            vector<int> now = q.front();
            int y = now[0];
            int x = now[1];
            for (int k = 0; k < 4; k++) {
                y += dir[k][0];
                x += dir[k][1];
                if (grid[y][x] == 0) {
                    grid[y][x] = 1;
                    q.push({y, x});
                } else if (grid[y][x] == 1) {
                    return count;
                }
            }

            q.pop();
            level--;
            if (level == 0) {
                count++;
                level = q.size();
            }

            printG(grid);
            */

        }
        return -10086;
    }

    void infect(vector<vector<int>>& grid, int lenY, int lenX, int y, int x) {
        // 基线
        if (y < 0 || y >= lenY) { return;}
        if (x < 0 || x >= lenX) { return;}
        if (grid[y][x] != 1) { return;}

        // 递归
        grid[y][x] = 2;
        q.push({y, x});
        for (int k = 0; k < 4; k++) {
            int yo = y + dir[k][0];
            int xo = x + dir[k][1];
            // printG(grid);
            infect(grid, lenY, lenX, yo, xo);
        }
    }

    void printG(vector<vector<int>>& grid) {
        int lenY = grid.size();
        int lenX = grid[0].size();
        for (int i = 0; i < lenY; i++) {
            for (int j = 0; j < lenX; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};


int main() {
    Solution solution;

    vector<vector<int>> grid = {
            {1,1,1,1,1},
            {1,0,0,0,1},
            {1,0,1,0,1},
            {1,0,0,0,1},
            {1,1,1,1,1}
    };
    cout << solution.shortestBridge(grid) << endl;

    return 0;
}

