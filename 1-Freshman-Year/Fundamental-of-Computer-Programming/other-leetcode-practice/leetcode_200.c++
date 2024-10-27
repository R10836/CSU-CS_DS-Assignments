//
// Created by Shawn33712 on 24-8-28.
//

/*
200. 岛屿数量
中等
相关标签
相关企业
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。



示例 1：

输入：grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
输出：1
示例 2：

输入：grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
输出：3


提示：

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] 的值为 '0' 或 '1'
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    // x、y、width、height 一定要对应准确！

    // 还可以用bfs实现！！

    int numIslands(vector<vector<char>>& grid) {
        // 准备工作
        int result = 0;
        int height = grid.size();
        int width = grid[0].size();
        vector<vector<bool>> visited(height, vector<bool>(width, false));

        // 传染法（递归/分治）
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (!visited[y][x] && grid[y][x] == '1') {  // 找到一个新大陆
                    result++;
                    infect(grid, visited, x, y);  // 将与其链接的陆地都标记上true
                }
            }
        }

        // 返回
        return result;
    }

    void infect(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
        // 基线
        int height = grid.size();
        int width = grid[0].size();
        if (y < 0 || y >= height || x < 0 || x >= width) {  // 超出边界
            return;
        }
        if (visited[y][x] || grid[y][x] =='0') {  // 已访问或海洋
            return;
        }

        // 递归
        visited[y][x] = true;
        infect(grid, visited, x, y + 1);
        infect(grid, visited, x, y - 1);
        infect(grid, visited, x - 1, y);
        infect(grid, visited, x + 1, y);
    }
};

int main() {
    Solution solution;

    vector<vector<char>> grid = {
            {'1', '1', '0', '0', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '1', '0', '0'},
            {'0', '0', '0', '1', '1'}
    };
    cout << solution.numIslands(grid) << endl;

    return 0;
}
