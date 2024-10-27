//
// Created by Shawn33712 on 24-8-22.
//

/*
1049. 最后一块石头的重量 II
中等
相关标签
相关企业
提示
有一堆石头，用整数数组 stones 表示。其中 stones[i] 表示第 i 块石头的重量。

每一回合，从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <= y。那么粉碎的可能结果如下：

如果 x == y，那么两块石头都会被完全粉碎；
如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。
最后，最多只会剩下一块 石头。返回此石头 最小的可能重量 。如果没有石头剩下，就返回 0。



示例 1：

输入：stones = [2,7,4,1,8,1]
输出：1
解释：
组合 2 和 4，得到 2，所以数组转化为 [2,7,1,8,1]，
组合 7 和 8，得到 1，所以数组转化为 [2,1,1,1]，
组合 2 和 1，得到 1，所以数组转化为 [1,1,1]，
组合 1 和 1，得到 0，所以数组转化为 [1]，这就是最优值。
示例 2：

输入：stones = [31,26,33,21,40]
输出：5


提示：

1 <= stones.length <= 30
1 <= stones[i] <= 100
*/

#include "iostream"
#include "vector"
#include "numeric"  // 如果你想要对容器中的元素求和，可以使用<numeric>库中的std::accumulate函数

using namespace std;


class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        // 初始化
        int stoneSize = stones.size();
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int target = sum / 2;

        // 01背包
        vector<vector<int>> dp(stoneSize, vector<int>(target + 1, 0));  // 初始化dp数组，大小为 行：stoneSize, 列：(target + 1)。
        for (int j = 0; j <= target; j++) {  // 初始化第一行
            if (j >= stones[0]) {
                dp[0][j] = stones[0];
            }
        }
        for (int i = 1; i < stoneSize; i++) {  // 填充dp数组
            for (int j = 0; j <= target; j++) {
                if (j - stones[i] >= 0) {  // 确保数组不越界
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j-stones[i]] + stones[i]);
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }

        // 测试
        printDP(dp, stoneSize-1, target);

        // 返回
        return sum - 2 * dp[stoneSize-1][target];
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

    vector<int> stones = {2,7,4,1,8,1};
    cout << solution.lastStoneWeightII(stones);

    return 0;
}

// 时间复杂度
// O(N∗Target)
