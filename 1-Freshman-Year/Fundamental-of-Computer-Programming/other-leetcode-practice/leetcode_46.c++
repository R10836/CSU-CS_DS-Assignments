//
// Created by Shawn33712 on 24-8-26.
//

/*
46. 全排列
中等
相关标签
相关企业
给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。



示例 1：

输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
示例 2：

输入：nums = [0,1]
输出：[[0,1],[1,0]]
示例 3：

输入：nums = [1]
输出：[[1]]


提示：

1 <= nums.length <= 6
-10 <= nums[i] <= 10
nums 中的所有整数 互不相同
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    vector<vector<int>> result;

    vector<int> path;

    vector<vector<int>> permute(vector<int>& nums) {
        backtracking(nums);
        return result;
    }

    void backtracking(vector<int>& nums) {
        // 基线
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }

        // 递归
        for (int i = 0; i < nums.size(); i++) {
            bool cf = false;
            for (int j = 0; j < path.size(); j++) {
                if (path[j] == nums[i]) {
                    cf = true;
                    break;
                }
            }
            if (cf) {
                continue;
            }
            path.push_back(nums[i]);
            backtracking(nums);
            path.pop_back();
        }
    }
};


int main() {
    Solution solution;

    vector<int> nums = {1,2,3};
    vector<vector<int>> answer = solution.permute(nums);
    for (int i = 0; i < answer.size(); i++) {
        for (int j = 0; j < answer[i].size(); j++) {
            cout << answer[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
