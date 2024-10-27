//
// Created by Shawn33712 on 24-8-29.
//

/*
977. 有序数组的平方
简单
相关标签
相关企业
给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。



示例 1：

输入：nums = [-4,-1,0,3,10]
输出：[0,1,9,16,100]
解释：平方后，数组变为 [16,1,0,9,100]
排序后，数组变为 [0,1,9,16,100]
示例 2：

输入：nums = [-7,-3,2,3,11]
输出：[4,9,9,49,121]


提示：

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums 已按 非递减顺序 排序
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    //时间复杂度
    //O(N)
    vector<int> sortedSquares(vector<int>& nums) {
        int len = nums.size();
        int i = 0, j = len - 1;
        vector<int> result(len, 0);
        for (int k = len - 1; k >= 0; k--) {
            if (abs(nums[i]) <= nums[j]) {
                result[k] = nums[j] * nums[j];
                j--;
            } else {
                result[k] = nums[i] * nums[i];
                i++;
            }
        }
        return result;
    }
    //通过
    //用时: 12 m 24 s
    //Eastwood
    //Eastwood
    //提交于 2024.08.29 19:57
};


int main() {
    Solution solution;

    vector<int> nums = {-7,-3,2,3,11};
    vector<int> answer = solution.sortedSquares(nums);
    for (int i = 0; i < answer.size(); i++) {
        cout << answer[i] << " ";
    }
    cout << endl;

    return 0;
}