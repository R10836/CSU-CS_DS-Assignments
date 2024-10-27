//
// Created by Shawn33712 on 24-8-23.
//

/*
70. 爬楼梯
简单
相关标签
相关企业
提示
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？



示例 1：

输入：n = 2
输出：2
解释：有两种方法可以爬到楼顶。
1. 1 阶 + 1 阶
2. 2 阶
示例 2：

输入：n = 3
输出：3
解释：有三种方法可以爬到楼顶。
1. 1 阶 + 1 阶 + 1 阶
2. 1 阶 + 2 阶
3. 2 阶 + 1 阶


提示：

1 <= n <= 45
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    int climbStairs(int n) {
        // dp数组定义：爬到第i阶有dp[i]种方法
        vector<int> dp(n + 1, 1);  // 上到第0层也是1种方法
        // dp初始化
        dp[1] = 1;
        // 递推公式
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        // 返回
        return dp[n];
    }
};


int main() {
    Solution solution;

    int n = 3;
    cout << solution.climbStairs(n) <<endl;

    return 0;
}
