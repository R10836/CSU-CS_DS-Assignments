//
// Created by Shawn33712 on 24-8-22.
//

/*
416. 分割等和子集
中等
相关标签
相关企业
给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。



示例 1：

输入：nums = [1,5,11,5]
输出：true
解释：数组可以分割成 [1, 5, 5] 和 [11] 。
示例 2：

输入：nums = [1,2,3,5]
输出：false
解释：数组不能分割成两个元素和相等的子集。


提示：

1 <= nums.length <= 200
1 <= nums[i] <= 100

*/

#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;


class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // 初试化
        int length = nums.size();
        int sum = 0;

        // 特殊情况
        if (length <= 1) {
            return false;
        }
        for (int i = 0; i < length; i++) {
            sum += nums[i];
        }
        if (sum % 2 != 0) {
            return false;
        }

        // 01背包
        int target = sum / 2;
        int dp[10001] = {0};
        for (int i = 0; i < length; i++) {
            for (int j = target; j >= nums[i]; j--) {
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
            }
        }
        if (dp[target] == target) {
            return true;
        }
        return false;
    }
};


int main() {
    Solution solution;

    vector<int> nums = {2,2,1,1};
    cout << boolalpha << solution.canPartition(nums) << endl;

    return 0;
}
