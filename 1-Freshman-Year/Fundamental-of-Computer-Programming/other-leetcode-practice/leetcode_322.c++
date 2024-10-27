//
// Created by Shawn33712 on 24-10-9.
//

/*
322. 零钱兑换
中等
相关标签
相关企业
给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。

计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。

你可以认为每种硬币的数量是无限的。



示例 1：

输入：coins = [1, 2, 5], amount = 11
输出：3
解释：11 = 5 + 5 + 1
示例 2：

输入：coins = [2], amount = 3
输出：-1
示例 3：

输入：coins = [1], amount = 0
输出：0


提示：

1 <= coins.length <= 12
1 <= coins[i] <= 231 - 1
0 <= amount <= 104
*/

#include "iostream"
#include "vector"
#include "algorithm"
#include "cmath"

using namespace std;


class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // 准备
        // sort(coins.begin(), coins.end());
        // std::reverse(coins.begin(), coins.end());
        int iLen = coins.size();
        int maxer = pow(2, 31) - 1;

        // dp
        vector<int> dp(amount + 1, maxer);

        // 初始化
        dp[0] = 0;

        // 递推公式
        for (int j = 1; j <= amount; j++) {
            for (int i = 0; i < iLen; i++) {
                if (j - coins[i] >= 0 && dp[j - coins[i]] != maxer) {
                    dp[j] = min(dp[j - coins[i]] + 1, dp[j]);
                }
            }
        }

        // 打印
        // for (int j = 0; j <= amount; j++) {
        //     cout << dp[j] << " ";
        // }
        // cout << endl;

        // 返回
        if (dp[amount] == maxer) {
            return -1;
        }
        return dp[amount];
    }
};


int main() {
    Solution solution;

    vector<int> coins = {2};
    int amount = 3;
    cout << solution.coinChange(coins, amount) << endl;

    return 0;
}
