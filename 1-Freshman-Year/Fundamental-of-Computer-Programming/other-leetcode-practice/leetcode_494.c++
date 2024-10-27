//
// Created by Shawn33712 on 24-8-22.
//

/*
494. 目标和
中等
相关标签
相关企业
给你一个非负整数数组 nums 和一个整数 target 。

向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：

例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。



示例 1：

输入：nums = [1,1,1,1,1], target = 3
输出：5
解释：一共有 5 种方法让最终目标和为 3 。
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3
示例 2：

输入：nums = [1], target = 1
输出：1


提示：

1 <= nums.length <= 20
0 <= nums[i] <= 1000
0 <= sum(nums[i]) <= 1000
-1000 <= target <= 1000
*/

#include "iostream"
#include "vector"
#include "numeric"

using namespace std;


// 回溯解法
class Solution {
    // 分为两个数组pos和neg，则pos-neg=target,即pos-(sum-pos)=target,解得pos=(target+sum)/2。
public:
    int result = 0;

    int path = 0;

    int findTargetSumWays(vector<int>& nums, int target) {
        // 初始
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if ((target + sum) % 2 != 0) {
            return 0;
        }
        int pos = (target + sum) / 2;
        // 回溯
        backtracking(nums, pos, 0);
        if (pos == 0) {  // 特殊情况（pos为0时可全选为负号或正号皆可，故多加一个）
            result++;
        }
        return result;
    }

    void backtracking(vector<int>& nums, int aim, int startIndex) {
        // 基线
        if (path > aim) {
            return;
        }
        // 递归
        for (int i = startIndex; i < nums.size(); i++) {
            path += nums[i];
            if (path == aim) {  // 因为可能加0，所以应该放这里即时result++。
                result++;
            }
            backtracking(nums, aim, i + 1);
            path -= nums[i];
        }
    }
};


// 动态规划解法
class Solution2 {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (abs(target) > sum) {
            return 0; // 此时没有方案
        }
        if ((target + sum) % 2 == 1) {
            return 0; // 此时没有方案
        }
        int bagSize = (target + sum) / 2;  // aim
        vector<int> dp(bagSize + 1, 0);  // 填满j（包括j）这么大容积的包，有dp[j]种方法
        dp[0] = 1;
        for (int i = 0; i < nums.size(); i++) {  // 物品
            for (int j = bagSize; j >= nums[i]; j--) {  // 背包，倒序
                dp[j] += dp[j - nums[i]];
            }
        }
        return dp[bagSize];
    }
};


int main() {
    Solution solution;
    Solution2 solution2;

    vector<int> nums = {2,3,1,2,1};
    vector<int> nums2 = {1000};
    vector<int> nums3 = {0,0,0};
    int target = 3;
    int target2 = -1000;
    int target3 = 0;

    cout << solution.findTargetSumWays(nums, target) << endl;
    cout << solution2.findTargetSumWays(nums, target) << endl;

    return 0;
}
