//
// Created by Shawn33712 on 24-8-19.
//

/*
216. 组合总和 III
中等
相关标签
相关企业
找出所有相加之和为 n 的 k 个数的组合，且满足下列条件：

只使用数字1到9
每个数字 最多使用一次
返回 所有可能的有效组合的列表 。该列表不能包含相同的组合两次，组合可以以任何顺序返回。



示例 1:

输入: k = 3, n = 7
输出: [[1,2,4]]
解释:
1 + 2 + 4 = 7
没有其他符合的组合了。
示例 2:

输入: k = 3, n = 9
输出: [[1,2,6], [1,3,5], [2,3,4]]
解释:
1 + 2 + 6 = 9
1 + 3 + 5 = 9
2 + 3 + 4 = 9
没有其他符合的组合了。
示例 3:

输入: k = 4, n = 1
输出: []
解释: 不存在有效的组合。
在[1,9]范围内使用4个不同的数字，我们可以得到的最小和是1+2+3+4 = 10，因为10 > 1，没有有效的组合。


提示:

2 <= k <= 9
1 <= n <= 60
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    vector<vector<int>> result;

    vector<int> path;

    int sum = 0;

    vector<vector<int>> combinationSum3(int k, int n) {
//        backtracking(k, n,1);
        backtrackingWithCut(k, n,1);
        return result;
    }

    void backtracking(int k, int n, int startIndex) {
        // 基线
        if (path.size() == k && sum == n) {
            result.push_back(path);
            return;
        }

        // 递归
        for (int i = startIndex; i <= 9; i++) {  // 需剪枝
            path.push_back(i); sum += i;
            backtracking(k, n, i + 1);
            path.pop_back(); sum -= i;
        }
    }

    void backtrackingWithCut(int k, int n, int startIndex) {
        // 基线
        if (path.size() == k) {
            if (sum == n) {
                result.push_back(path);
                return;
            } else {  // 剪枝1：当数字个数到k时，没必要再往下搜了，不需要等待和为sum时再终止。
                return;
            }
        }

        // 递归
        for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++) {  // 剪枝2：当前路径长度加上剩余可选的数字数量不可能再达到k，就没必要继续探索。
            if (sum + i > n) {  // 剪枝3：当前数字i加上sum已经超过n，后续的i更大，没必要等待sum或k。
                break;
            }
            path.push_back(i); sum += i;
            backtracking(k, n, i + 1);
            path.pop_back(); sum -= i;
        }
    }
};


int main() {
    Solution solution;

    int n = 9;
    int k = 3;

    vector<vector<int>> result = solution.combinationSum3(k, n);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
