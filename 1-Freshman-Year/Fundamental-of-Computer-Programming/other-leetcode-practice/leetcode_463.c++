//
// Created by Shawn33712 on 24-10-6.
//

/*
463. 岛屿的周长
简单
相关标签
相关企业
给定一个 row x col 的二维网格地图 grid ，其中：grid[i][j] = 1 表示陆地， grid[i][j] = 0 表示水域。

网格中的格子 水平和垂直 方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。

岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长。



示例 1：



输入：grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
输出：16
解释：它的周长是上面图片中的 16 个黄色的边
示例 2：

输入：grid = [[1]]
输出：4
示例 3：

输入：grid = [[1,0]]
输出：4


提示：

row == grid.length
col == grid[i].length
1 <= row, col <= 100
grid[i][j] 为 0 或 1
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    int count = 0;

    // 题目描述：恰好有一个岛屿
    int islandPerimeter(vector<vector<int>>& grid) {
        int ylen = grid.size();
        int xlen = grid[0].size();
        vector<vector<bool>> used(ylen, vector<bool>(xlen, false));

        for (int i = 0; i < ylen; i++) {
            for (int j = 0; j < xlen; j++) {
                if (grid[i][j] == 1) {
                    infect(i, j, ylen, xlen, grid, used);
                    return count;
                }
            }
        }
        return -10086;
    }

    void infect(int y, int x, int ylen, int xlen, vector<vector<int>>& grid, vector<vector<bool>>& used) {
        // 基线
        if (y < 0 || y >= ylen) {return;}
        if (x < 0 || x >= xlen) {return;}
        if (grid[y][x] == 0) {return;}
        if (used[y][x]) {return;}

        // 当前操作
        used[y][x] = true;
        count += 4;
        if ((y-1 >= 0 && y-1 < ylen) && grid[y-1][x] == 1) {count--;}
        if ((y+1 >= 0 && y+1 < ylen) && grid[y+1][x] == 1) {count--;}
        if ((x-1 >= 0 && x-1 < xlen) && grid[y][x-1] == 1) {count--;}
        if ((x+1 >= 0 && x+1 < xlen) && grid[y][x+1] == 1) {count--;}
//        cout << count << " ";

        // 递归
        infect(y-1, x, ylen, xlen, grid, used);
        infect(y+1, x, ylen, xlen, grid, used);
        infect(y, x-1, ylen, xlen, grid, used);
        infect(y, x+1, ylen, xlen, grid, used);
    }
};


int main() {
    Solution solution;

    vector<vector<int>> grid = {
            {0,1,0,0},
            {1,1,1,0},
            {0,1,0,0},
            {1,1,0,0}
    };
    cout << solution.islandPerimeter(grid) << endl;

    return 0;
}
