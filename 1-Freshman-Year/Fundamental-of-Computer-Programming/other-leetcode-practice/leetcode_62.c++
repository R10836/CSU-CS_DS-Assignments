//
// Created by Shawn33712 on 24-8-29.
//

/*
62. 不同路径
中等
相关标签
相关企业
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？



示例 1：


输入：m = 3, n = 7
输出：28
示例 2：

输入：m = 3, n = 2
输出：3
解释：
从左上角开始，总共有 3 条路径可以到达右下角。
1. 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右
3. 向下 -> 向右 -> 向下
示例 3：

输入：m = 7, n = 3
输出：28
示例 4：

输入：m = 3, n = 3
输出：6
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    int uniquePaths(int m, int n) {
        // 准备工作

        // dp定义
        vector<vector<int>> dp(m, vector<int>(n, 0));

        // 初始化
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }
        for (int j = 0; j < n; j++) {
            dp[0][j] = 1;
        }

        // 递推公式
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }

        // 打印
        printDP(dp, m-1, n-1);

        // 返回
        return dp[m-1][n-1];
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

    cout << solution.uniquePaths(3, 7) << endl;

    return 0;
}

//通过
//用时: 9 m 46 s
//Eastwood
//Eastwood
//提交于 2024.08.29 02:41
