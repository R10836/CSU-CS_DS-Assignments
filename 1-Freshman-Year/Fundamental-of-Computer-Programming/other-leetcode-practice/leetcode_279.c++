//
// Created by Shawn33712 on 24-9-4.
//

/*
279. 完全平方数
已解答
中等
相关标签
相关企业
给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。

完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。



示例 1：

输入：n = 12
输出：3
解释：12 = 4 + 4 + 4
示例 2：

输入：n = 13
输出：2
解释：13 = 4 + 9

提示：

1 <= n <= 104
*/


#include "iostream"
#include "vector"
#include "cmath"

using namespace std;


class Solution {
public:
    // O(N∗Sqrt(N))
    int numSquares(int n) {
        // 准备
        int m = sqrt(n);

        // dp
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

        // 初始化
        for (int j = 0; j <= n; j++) {
            dp[1][j] = j;
        }

        // 递推公式
        for (int i = 2; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (j - i*i >= 0) {
                    dp[i][j] = min(dp[i-1][j], dp[i][j-i*i] + 1);
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }

        // 打印
        printDP(dp, m, n);

        // 返回
        return dp[m][n];
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

    cout << solution.numSquares(12) << endl;

    return 0;
}
