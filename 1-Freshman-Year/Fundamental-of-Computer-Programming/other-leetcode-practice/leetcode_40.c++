//
// Created by Shawn33712 on 24-10-10.
//

/*
40. 组合总和 II
中等
相关标签
相关企业
给定一个候选人编号的集合 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用 一次 。

注意：解集不能包含重复的组合。



示例 1:

输入: candidates = [10,1,2,7,6,1,5], target = 8,
输出:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]
示例 2:

输入: candidates = [2,5,2,1,2], target = 5,
输出:
[
[1,2,2],
[5]
]


提示:

1 <= candidates.length <= 100
1 <= candidates[i] <= 50
1 <= target <= 30
*/

#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;


class Solution {
public:
    vector<vector<int>> result;

    vector<int> path;

    int count = 0;

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        int len = candidates.size();
        sort(candidates.begin(), candidates.end());
        vector<bool> used(len, false);

        backtracking(candidates, used, target, len, 0);

        return result;
    }

    void backtracking(vector<int>& candidates, vector<bool>& used, int target, int len, int startIndex) {
        // 基线
        if (count > target) {
            return;
        }
        if (count == target) {
            result.push_back(path);
            return;
        }

        // 回溯
        for (int i = startIndex; i < len; i++) {
            if (i > 0 && candidates[i] == candidates[i - 1] && !used[i - 1]) {
                // 如果当前的 candidates[i] 和前一个元素 candidates[i-1] 相等，且前一个元素没有被使用（即 used[i-1] == false），说明此时在同一层中会出现重复组合，应该跳过这个元素。
                continue;
            }

            used[i] = true;
            path.push_back(candidates[i]);
            count += candidates[i];

            backtracking(candidates, used, target, len, i+1);

            used[i] = false;
            path.pop_back();
            count -= candidates[i];
        }
    }
};


int main() {
    Solution solution;

    vector<int> candidates = {10,1,2,7,6,1,5};
    int target = 8;
    vector<vector<int>> output = solution.combinationSum2(candidates, target);
    for (int i = 0; i < output.size(); i++) {
        for (int j = 0; j < output[i].size(); j++) {
            cout << output[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
