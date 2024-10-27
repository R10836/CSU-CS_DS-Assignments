//
// Created by Shawn33712 on 24-8-24.
//

/*
121. 买卖股票的最佳时机
简单
相关标签
相关企业
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。



示例 1：

输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
示例 2：

输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。


提示：

1 <= prices.length <= 105
0 <= prices[i] <= 104
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    // 9-14贪心 超时
    int maxProfit2(vector<int>& prices) {
        int result = 0;
        for (int i = 0; i < prices.size()-1; i++) {
            for (int j = i; j < prices.size(); j++) {
                int gap = prices[j] - prices[i];
                if (gap > 0) {
                    result = max(result, gap);
                }
            }
        }
        return result;
    }

    // 9-14贪心
    int maxProfit3(vector<int>& prices) {
        int result = 0;
        int nowTop = INT_MIN;
        for (int i = prices.size()-1; i >= 0; i--) {
            nowTop = max(nowTop, prices[i]);
            result = max(result, nowTop - prices[i]);
        }
        return result;
    }

    // 9-14贪心2
    int maxProfit4(vector<int>& prices) {
        int result = 0;
        int nowLow = INT_MAX;
        for (int i = 0; i < prices.size(); i++) {
            nowLow = min(nowLow, prices[i]);
            result = max(result, prices[i] - nowLow);
        }
        return result;
    }

    // 超出内存限制 超出时间限制
    int maxProfit0(vector<int>& prices) {
        // 准备工作
        int priceSize = prices.size();
        // dp定义
        vector<vector<int>> dp(priceSize, vector<int> (priceSize, 0));
        // dp初始化
        // dp递推公式
        int maxProfit = 0;
        for (int i = 0; i < priceSize; i++) {
            for (int j = 0; j < priceSize; j++) {
                if (i < j) {
                    dp[i][j] = prices[j] - prices[i];
                    if (maxProfit < dp[i][j]) {
                        maxProfit = dp[i][j];
                    }
                }
            }
        }
        // 打印dp
        printDP(dp, priceSize - 1, priceSize - 1);
        // 返回
        return maxProfit;
    }

    // 超出时间限制
    int maxProfit1(vector<int>& prices) {
        // 准备工作
        int priceSize = prices.size();
        int maxProfit = 0;
        for (int i = 0; i < priceSize; i++) {
            for (int j = i + 1; j < priceSize; j++) {
                if (maxProfit < prices[j] - prices[i]) {
                    maxProfit =  prices[j] - prices[i];
                }
            }
        }
        return maxProfit;
    }

    int maxProfit(vector<int>& prices) {
        // 准备工作
        int priceSize = prices.size();
        // dp定义：
        // dp[0][j]是第i天持有这支股票所得的最大现金（买的当天算持有）
        // dp[1][j]是第i天不持有这支股票所得的最大现金（卖的当天算不持有）
        vector<vector<int>> dp(2, vector<int> (priceSize, 0));
        // dp初始化
        dp[0][0] = -prices[0];
        dp[1][0] = 0;
        // dp递推公式
        for (int j = 1; j < priceSize; j++) {
            dp[0][j] = max(dp[0][j-1], -prices[j]);
            dp[1][j] = max(dp[1][j-1], dp[0][j-1] + prices[j]);
        }
        // 打印dp
        printDP(dp, 1, priceSize - 1);
        // 返回
        return dp[1][priceSize-1];
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

    vector<int> prices = {7,1,5,3,6,4};
    cout << solution.maxProfit3(prices);

    return 0;
}
