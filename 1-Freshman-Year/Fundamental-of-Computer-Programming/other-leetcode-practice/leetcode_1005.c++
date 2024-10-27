//
// Created by Shawn33712 on 24-9-14.
//

/*
1005. K 次取反后最大化的数组和
简单
相关标签
相关企业
给你一个整数数组 nums 和一个整数 k ，按以下方法修改该数组：

选择某个下标 i 并将 nums[i] 替换为 -nums[i] 。
重复这个过程恰好 k 次。可以多次选择同一个下标 i 。

以这种方式修改数组后，返回数组 可能的最大和 。



示例 1：

输入：nums = [4,2,3], k = 1
输出：5
解释：选择下标 1 ，nums 变为 [4,-2,3] 。
示例 2：

输入：nums = [3,-1,0,2], k = 3
输出：6
解释：选择下标 (1, 2, 2) ，nums 变为 [3,1,0,2] 。
示例 3：

输入：nums = [2,-3,-1,5,-4], k = 2
输出：13
解释：选择下标 (1, 4) ，nums 变为 [2,3,-1,5,4] 。


提示：

1 <= nums.length <= 104
-100 <= nums[i] <= 100
1 <= k <= 104
*/

#include "iostream"
#include "vector"
#include "algorithm"
#include "numeric"

using namespace std;


class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int len = nums.size();

        int i = 0;
        while (nums[i] < 0) {
            nums[i] = -nums[i];
            i++;
            k--;
            if (k == 0) {
                return accumulate(nums.begin(), nums.end(), 0);
            }
            if (i >= len-1) {
                break;
            }
        }

        int over;
        if (i == 0) {
            over = nums[i];
        } else {
            over = min(nums[i], nums[i-1]);
        }

        if (k % 2 == 0) {
            return accumulate(nums.begin(), nums.end(), 0);
        } else {
            return accumulate(nums.begin(), nums.end(), 0) - 2 * over;
        }
    }
};


int main() {
    Solution solution;

    vector<int> nums = {2,-3,-1,5,-4};
    int k = 2;
    cout << solution.largestSumAfterKNegations(nums, k) << endl;

    return 0;
}
