//
// Created by Shawn33712 on 24-8-29.
//

/*
695. 岛屿的最大面积
中等
相关标签
相关企业
给你一个大小为 m x n 的二进制矩阵 grid 。

岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在 水平或者竖直的四个方向上 相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。

岛屿的面积是岛上值为 1 的单元格的数目。

计算并返回 grid 中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。



示例 1：


输入：grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
输出：6
解释：答案不应该是 11 ，因为岛屿只能包含水平或垂直这四个方向上的 1 。
示例 2：

输入：grid = [[0,0,0,0,0,0,0,0]]
输出：0


提示：

m == grid.length
n == grid[i].length
1 <= m, n <= 50
grid[i][j] 为 0 或 1
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    int result = 0;

    int path = 0;

    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int height = grid.size();
        int width = grid[0].size();

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (grid[y][x] == 1) {
                    path = 0;
                    infect(grid, y, x, height, width);
                    result = max(result, path);
                }
            }
        }

        return result;
    }

    void infect(vector<vector<int>>& grid, int y, int x, int height, int width) {
        // 基线
        if (y < 0 || y >= height || x < 0 || x >= width) {
            return;
        }
        if (grid[y][x] != 1) {
            return;
        }

        // 递归
        path++;
        grid[y][x] = 2;  // 2为已经传染
        infect(grid, y + 1, x, height, width);
        infect(grid, y - 1, x, height, width);
        infect(grid, y, x - 1, height, width);
        infect(grid, y, x + 1, height, width);
    }
};


int main() {
    Solution solution;

    vector<vector<int>> grid = {
            {0,0,1,0,0,0,0,1,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,1,1,0,1,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,1,0,0,1,0,1,0,0},
            {0,1,0,0,1,1,0,0,1,1,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,1,0,0},
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,0,0,0,0,0,0,1,1,0,0,0,0}
    };
    cout << solution.maxAreaOfIsland(grid) << endl;

    return 0;
}
