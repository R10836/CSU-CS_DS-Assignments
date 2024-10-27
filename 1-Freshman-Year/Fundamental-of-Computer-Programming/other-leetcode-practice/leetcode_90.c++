//
// Created by Shawn33712 on 24-8-22.
//

/*
90. 子集 II
中等
相关标签
相关企业
给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的
子集
（幂集）。

解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。



示例 1：

输入：nums = [1,2,2]
输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
示例 2：

输入：nums = [0]
输出：[[],[0]]


提示：

1 <= nums.length <= 10
-10 <= nums[i] <= 10
*/

#include "iostream"
#include "vector"
#include "set"
#include "algorithm"

using namespace std;


class Solution {
public:
    vector<vector<int>> result = {{}};

    vector<int> path;

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // 为了解决重复问题，可以将相同的元素放在一起。故这里用了排序以将相同的元素放在一起。
        backtracking(nums, 0);
        return result;
    }

    void backtracking(vector<int>& nums, int startIndex) {
        // 基线

        // 递归
        set<int> death;  // 使用过的元素
        for (int i = startIndex; i < nums.size(); i++) {
            if (death.count(nums[i]) == 0) {
                death.insert(nums[i]);
                path.push_back(nums[i]);
                result.push_back(path);
                backtracking(nums, i + 1);
                path.pop_back();
            }
        }
    }
};


int main() {
    Solution solution;

    vector<int> nums = {2,2,1,5,2};
    vector<vector<int>> result = solution.subsetsWithDup(nums);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
