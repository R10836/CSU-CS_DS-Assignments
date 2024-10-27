//
// Created by Shawn33712 on 24-10-7.
//

/*
1020. 飞地的数量
中等
相关标签
相关企业
提示
给你一个大小为 m x n 的二进制矩阵 grid ，其中 0 表示一个海洋单元格、1 表示一个陆地单元格。

一次 移动 是指从一个陆地单元格走到另一个相邻（上、下、左、右）的陆地单元格或跨过 grid 的边界。

返回网格中 无法 在任意次数的移动中离开网格边界的陆地单元格的数量。



示例 1：


输入：grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
输出：3
解释：有三个 1 被 0 包围。一个 1 没有被包围，因为它在边界上。
示例 2：


输入：grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
输出：0
解释：所有 1 都在边界上或可以到达边界。


提示：

m == grid.length
n == grid[i].length
1 <= m, n <= 500
grid[i][j] 的值为 0 或 1
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int count = 0;
        int lenY = grid.size();
        int lenX = grid[0].size();

        for (int i = 0; i < lenY; i++) {
            if (grid[i][0] == 1) {
                infect(grid, i, 0, lenY, lenX);
            }
            if (grid[i][lenX-1] == 1) {
                infect(grid, i, lenX-1, lenY, lenX);
            }
        }
        for (int j = 0; j < lenX; j++) {
            if (grid[0][j] == 1) {
                infect(grid, 0, j, lenY, lenX);
            }
            if (grid[lenY-1][j] == 1) {
                infect(grid, lenY-1, j, lenY, lenX);
            }
        }

        for (int i = 0; i < lenY; i++) {
            for (int j = 0; j < lenX; j++) {
                if (grid[i][j] == 1) {
                    count++;
                }
            }
        }

        return count;
    }

    void infect(vector<vector<int>>& grid, int y, int x, int lenY, int lenX) {
        // 基线
        if (x < 0 || x >= lenX) {
            return;
        }
        if (y < 0 || y >= lenY) {
            return;
        }

        // 迭代
        if (grid[y][x] == 1) {
            grid[y][x] = 0;
            infect(grid, y-1, x, lenY, lenX);
            infect(grid, y+1, x, lenY, lenX);
            infect(grid, y, x-1, lenY, lenX);
            infect(grid, y, x+1, lenY, lenX);
        }
    }
};


int main() {
    Solution solution;

    vector<vector<int>> grid = {
            {0,0,0,1,1,1,0,1,0,0},
            {1,1,0,0,0,1,0,1,1,1},
            {0,0,0,1,1,1,0,1,0,0},
            {0,1,1,0,0,0,1,0,1,0},
            {0,1,1,1,1,1,0,0,1,0},
            {0,0,1,0,1,1,1,1,0,1},
            {0,1,1,0,0,0,1,1,1,1},
            {0,0,1,0,0,1,0,1,0,1},
            {1,0,1,0,1,1,0,0,0,0},
            {0,0,0,0,1,1,0,0,0,1}
    };
    cout << solution.numEnclaves(grid) << endl;

    return 0;
}
