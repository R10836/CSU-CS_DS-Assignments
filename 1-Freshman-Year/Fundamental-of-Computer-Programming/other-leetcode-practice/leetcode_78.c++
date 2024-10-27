//
// Created by Shawn33712 on 24-8-20.
//

/*
78. 子集
中等
相关标签
相关企业
给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的
子集
（幂集）。

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。



示例 1：

输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
示例 2：

输入：nums = [0]
输出：[[],[0]]


提示：

1 <= nums.length <= 10
-10 <= nums[i] <= 10
nums 中的所有元素 互不相同
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    vector<vector<int>> result = {{}};  // 加上空集

    vector<int> path;

    vector<vector<int>> subsets(vector<int>& nums) {
        backtracking(nums, 0);
        return result;
    }

    void backtracking(vector<int>& nums, int startIndex) {
        // 基线

        // 迭代
        for (int i = startIndex; i < nums.size(); i++) {
            path.push_back(nums[i]);
            result.push_back(path);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
};


int main() {
    Solution solution;

    vector<int> nums = {2,5,8,0};

    vector<vector<int>> result = solution.subsets(nums);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
