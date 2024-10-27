//
// Created by Shawn33712 on 24-8-24.
//

/*
518. 零钱兑换 II
中等
相关标签
相关企业
给你一个整数数组 coins 表示不同面额的硬币，另给一个整数 amount 表示总金额。

请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回 0 。

假设每一种面额的硬币有无限个。

题目数据保证结果符合 32 位带符号整数。



示例 1：

输入：amount = 5, coins = [1, 2, 5]
输出：4
解释：有四种方式可以凑成总金额：
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
示例 2：

输入：amount = 3, coins = [2]
输出：0
解释：只用面额 2 的硬币不能凑成总金额 3 。
示例 3：

输入：amount = 10, coins = [10]
输出：1


提示：

1 <= coins.length <= 300
1 <= coins[i] <= 5000
coins 中的所有值 互不相同
0 <= amount <= 5000
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    int change(int amount, vector<int>& coins) {
        // 准备工作
        int coinSize = coins.size();
        // dp定义：凑成总面额为j的方法有dp[j]种
        vector<vector<int>> dp(coinSize, vector<int>(amount + 1, 0));
        // 初始dp
        for (int i = 0; i < coinSize; i++) {
            dp[i][0] = 1;
        }
        for (int j = 0; j <= amount; j++) {
            if (j % coins[0] == 0) {
                dp[0][j] = 1;
            }
        }
        // 递推公式
        for (int i = 1; i < coinSize; i++) {
            for (int j = 1; j <= amount; j++) {
                if (j - coins[i] >= 0) {
                    dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]];
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        // 打印
        printDP(dp, coinSize - 1, amount);
        // 返回
        return dp[coinSize-1][amount];
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

    vector<int> coins = {3};
    int amount = 2;

    cout << solution.change(amount, coins) << endl;

    return 0;
}