//
// Created by Shawn33712 on 24-8-21.
//

/*
509. 斐波那契数
简单
相关标签
相关企业
斐波那契数 （通常用 F(n) 表示）形成的序列称为 斐波那契数列 。该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。也就是：

F(0) = 0，F(1) = 1
F(n) = F(n - 1) + F(n - 2)，其中 n > 1
给定 n ，请计算 F(n) 。



示例 1：

输入：n = 2
输出：1
解释：F(2) = F(1) + F(0) = 1 + 0 = 1
示例 2：

输入：n = 3
输出：2
解释：F(3) = F(2) + F(1) = 1 + 1 = 2
示例 3：

输入：n = 4
输出：3
解释：F(4) = F(3) + F(2) = 2 + 1 = 3


提示：

0 <= n <= 30
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    // 递归解法
    int fib_0(int n) {
        // 基线
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return 1;
        }
        // 递归
        return fib_0(n - 1) + fib_0(n - 2);
    }

    // 动态规划解法
    int fib(int N) {
        if (N <= 1) return N;
        vector<int> dp(N + 1);
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= N; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[N];
    }
};


int main() {
    Solution solution;

    int n = 4;
    cout << solution.fib(n);

    return 0;
}

// dp数组以及下标的含义
// 递推公式
// dp数组如何初始化
// 遍历顺序
// 打印dp数组
