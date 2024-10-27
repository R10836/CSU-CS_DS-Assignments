//
// Created by Shawn33712 on 24-8-26.
//

/*
674. 最长连续递增序列
简单
相关标签
相关企业
给定一个未经排序的整数数组，找到最长且 连续递增的子序列，并返回该序列的长度。

连续递增的子序列 可以由两个下标 l 和 r（l < r）确定，如果对于每个 l <= i < r，都有 nums[i] < nums[i + 1] ，那么子序列 [nums[l], nums[l + 1], ..., nums[r - 1], nums[r]] 就是连续递增子序列。



示例 1：

输入：nums = [1,3,5,4,7]
输出：3
解释：最长连续递增序列是 [1,3,5], 长度为3。
尽管 [1,3,5,7] 也是升序的子序列, 但它不是连续的，因为 5 和 7 在原数组里被 4 隔开。
示例 2：

输入：nums = [2,2,2,2,2]
输出：1
解释：最长连续递增序列是 [2], 长度为1。


提示：

1 <= nums.length <= 104
-109 <= nums[i] <= 109
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        // 准备工作
        int numSize = nums.size();
        int maxSeq = 1;
        // dp
        vector<int> dp(numSize, 0);
        // 初始化
        dp[0] = 1;
        // 递推公式
        for (int i = 1; i < numSize; i++) {
            if (nums[i-1] < nums[i]) {
                dp[i] = dp[i-1] + 1;
                maxSeq = max(maxSeq, dp[i]);
            } else {
                dp[i] = 1;
            }
        }
        // 打印
        // for (int i = 0; i < dp.size(); i++) {
        //     cout << dp[i] << " ";
        // }
        // cout << endl;
        // 返回
        return maxSeq;
    }
};


int main() {
    Solution solution;

    vector<int> nums = {9,1,2,3,-1,4,5,6,6};
    cout << solution.findLengthOfLCIS(nums) << endl;

    return 0;
}

//执行用时分布
//3
//ms
//击败
//96.93%
