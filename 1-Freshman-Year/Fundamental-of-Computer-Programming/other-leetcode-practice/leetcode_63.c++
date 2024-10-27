//
// Created by Shawn33712 on 24-9-5.
//

/*
63. 不同路径 II
中等
相关标签
相关企业
提示
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

网格中的障碍物和空位置分别用 1 和 0 来表示。



示例 1：


输入：obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
输出：2
解释：3x3 网格的正中间有一个障碍物。
从左上角到右下角一共有 2 条不同的路径：
1. 向右 -> 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右 -> 向右
示例 2：


输入：obstacleGrid = [[0,1],[0,0]]
输出：1


提示：

m == obstacleGrid.length
n == obstacleGrid[i].length
1 <= m, n <= 100
obstacleGrid[i][j] 为 0 或 1
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    // O(M∗N)
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        // 准备
        int row = obstacleGrid.size();
        int col = obstacleGrid[0].size();

        // dp
        vector<vector<int>> dp(row, vector<int>(col, 0));

        // 初始化
        if (obstacleGrid[0][0] == 0) {
            dp[0][0] = 1;
        }
        for (int i = 1; i < row; i++) {
            if (obstacleGrid[i][0] == 0) {
                dp[i][0] = dp[i-1][0];
            }
        }
        for (int j = 1; j < col; j++) {
            if (obstacleGrid[0][j] == 0) {
                dp[0][j] = dp[0][j-1];
            }
        }

        // 递推公式
        for (int i = 1; i < row; i++) {
            for (int j = 1; j < col; j++) {
                if (obstacleGrid[i][j] == 0) {
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }
            }
        }

        // 打印
        printDP(dp, row-1, col-1);

        // 返回
        return dp[row-1][col-1];
    }

    void printDP(vector<vector<int>>& dp, int iMax, int jMax) {
        // 数组最后一个元素为dp[iMax][jMax]
        for (int i = 0; i <= iMax; i++) {
            for (int j = 0; j <= jMax; j++) {
                cout << dp[i][j] << "\t";
            }
            cout << endl;
        }
    }
};


int main() {
    Solution solution;

    vector<vector<int>> obstacleGrid = {
            {0,0,0},
            {0,1,0},
            {0,0,0}
    };
    cout << solution.uniquePathsWithObstacles(obstacleGrid) << endl;

    return 0;
}
