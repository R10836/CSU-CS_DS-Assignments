//
// Created by Shawn33712 on 24-8-25.
//

/*
300. 最长递增子序列
中等
相关标签
相关企业
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的
子序列
。


示例 1：

输入：nums = [109,2,5,3,7,101,18]
输出：4
解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。,
示例 2：

输入：nums = [0,1,0,3,2,3]
输出：4
示例 3：

输入：nums = [7,7,7,7,7,7,7]
输出：1


提示：

1 <= nums.length <= 2500
-104 <= nums[i] <= 104


进阶：

你能将算法的时间复杂度降低到 O(n log(n)) 吗?
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    void printDP_1(int dp[], int dpEnd) {
        for (int i = 0; i <= dpEnd; i++) {
            cout << dp[i] << " ";
        }
        cout << endl;
    }

    // O(n^2)
    int lengthOfLIS(vector<int>& nums) {
        // 准备工作
        int numSize = nums.size();
        int allMax = 1;
        // dp定义：以nums[i]这个元素结尾的最长递增子序列的长度
        int dp[numSize];
        // dp初始化
        dp[0] = 1;
        // dp递推公式
        for (int i = 1; i < numSize; i++) {
            int tempMax = 0;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    tempMax = max(tempMax, dp[j]);
                }
            }
            dp[i] = tempMax + 1;
            allMax = max(allMax, dp[i]);
        }
        // 打印dp
        printDP_1(dp, numSize - 1);
        // 返回
        return allMax;
    }

    // O(n logn)
    int lengthOfLIS_nlogn(vector<int>& nums) {
        if (nums.empty()) return 0;
        // 辅助数组，存储当前构建的递增子序列
        vector<int> dp;
        dp.push_back(nums[0]);
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > dp.back()) {
                // 如果当前元素大于dp中的最大值，则直接放在dp的末尾，扩展最长子序列
                dp.push_back(nums[i]);
            } else {
                // 否则，使用二分查找找到dp中第一个大于或等于nums[i]的位置，并替换之
                auto it = lower_bound(dp.begin(), dp.end(), nums[i]);
                *it = nums[i];
            }
        }
        // 打印dp
        // dp数组的长度即为最长递增子序列的长度
        return dp.size();
    }
};


int main() {
    Solution solution;

    vector<int> nums = {10,9,2,5,3,7,101,18};
    cout << solution.lengthOfLIS(nums) << endl;

    return 0;
}
