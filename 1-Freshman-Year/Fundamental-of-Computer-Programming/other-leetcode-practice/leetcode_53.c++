//
// Created by Shawn33712 on 24-9-14.
//

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    // 局部最优：前面的连续和为负时，对于后面的被加数，没有增加作用；重新开始计算。
    // 全局最优：在数组中找到最大连续子数组的和。
    int maxSubArray(vector<int>& nums) {
        int result = -INT_MAX;
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            result = max(result, sum);
            if (sum < 0) {
                sum = 0;
            }
        }
        return result;
    }
};


int main() {
    Solution solution;

    vector<int> nums = {-21,-5};
    cout << solution.maxSubArray(nums) << endl;

    return 0;
}
