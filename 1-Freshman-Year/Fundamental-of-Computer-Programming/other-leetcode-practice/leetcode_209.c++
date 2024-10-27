//
// Created by Shawn33712 on 24-8-15.
//
/*
209. 长度最小的子数组
中等
相关标签
相关企业
给定一个含有 n 个正整数的数组和一个正整数 target 。

找出该数组中满足其总和大于等于 target 的长度最小的
子数组
 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。



示例 1：

输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
示例 2：

输入：target = 4, nums = [1,4,4]
输出：1
示例 3：

输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0


提示：

1 <= target <= 109
1 <= nums.length <= 105
1 <= nums[i] <= 105


进阶：

如果你已经实现 O(n) 时间复杂度的解法, 请尝试设计一个 O(n log(n)) 时间复杂度的解法。
*/


#include "iostream"
#include "vector"
#include "cstdint"

using namespace std;


class Solution {
public:
    int violentMinSubArrayLen(int target, vector<int>& nums) {
        int minLen = 0;
        for (int i = 0; i < nums.size(); i++) {
            int len = 0;
            int sum = 0;
            for (int j = i; j < nums.size(); j++) {
                if (sum < target) {
                    sum += nums[j];
                    len++;
                }
                if (sum >= target) {
                    if (minLen == 0) {
                        minLen = len;
                    }
                    if (len > minLen) {
                        break;
                    }
                    if (len < minLen) {
                        minLen = len;
                    }
                    break;
                }
            }
        }
        return minLen;
    }

    int minSubArrayLen(int target, vector<int>& nums) {
        int minLen = INT32_MAX;
        int sum = 0;
        int i = 0;
        for (int j = 0; j < nums.size(); j++) {
            sum += nums[j];
            while (sum >= target) {
                int len = j - i + 1;
                minLen = min(minLen, len);
                sum -= nums[i];
                i++;
            }
        }
        return minLen == INT32_MAX ? 0 : minLen;
    }
};


int main() {
    vector<int> nums = {1,1,1,1,1,1,1,1};
    int target = 71;

    Solution sol;

//    int subLength = sol.violentMinSubArrayLen(target, nums);
//    cout << subLength << endl;
    int subLength2 = sol.minSubArrayLen(target, nums);
    cout << subLength2 << endl;

    return 0;
}

/*

*/