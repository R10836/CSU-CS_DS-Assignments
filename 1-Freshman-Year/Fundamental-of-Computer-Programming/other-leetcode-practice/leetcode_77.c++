//
// Created by Shawn33712 on 24-8-18.
//

/*
77. 组合
中等
相关标签
相关企业
给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。

你可以按 任何顺序 返回答案。



示例 1：

输入：n = 4, k = 2
输出：
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
示例 2：

输入：n = 1, k = 1
输出：[[1]]


提示：

1 <= n <= 20
1 <= k <= n
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
private:
    // 初始化
    vector<vector<int>> result;

    vector<int> path;

    void backtracking(int startIndex, int n, int k) {
        // 基线
        if (path.size() == k) {
            result.push_back(path);
            return;
        }

        // 递归
        for (int i = startIndex; i <= n - (k - path.size()) + 1; i++) {
            path.push_back(i);
            backtracking(i + 1, n, k);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combine(int n, int k) {
        backtracking(1, n, k);
        return result;
    }
};


int main() {
    Solution solution;

    int n = 5;
    int k = 3;

    vector<vector<int>> out = solution.combine(n, k);
    for (int i = 0; i < out.size(); i++) {
        for (int j = 0; j < out[i].size(); j++) {
            cout << out[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

// 回溯相当于是利用递归来控制有多少层for循环