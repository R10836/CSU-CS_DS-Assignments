//
// Created by Shawn33712 on 24-8-20.
//

/*
131. 分割回文串
中等
相关标签
相关企业
给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是
回文串
 。返回 s 所有可能的分割方案。



示例 1：

输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]
示例 2：

输入：s = "a"
输出：[["a"]]


提示：

1 <= s.length <= 16
s 仅由小写英文字母组成
*/

#include "iostream"
#include "vector"
#include "string"

using namespace std;


class Solution {
public:
    vector<vector<string>> result;

    vector<string> path;

    vector<vector<string>> partition(string s) {
        backtracking(s);
//        backtrackingGPT(s, 0);
        return result;
    }

    void backtracking(string s) {
        // 基线
        if (s.empty()) {
            result.push_back(path);
            return;
        }

        // 递归
        for (int i = 1; i <= s.size(); i++) {
            string s_1 = s.substr(0, i);
            if (! isPalindrome(s_1)) {
                continue;
            }
            string s_2 = s.substr(i);
            path.push_back(s_1);
            backtracking(s_2);
            path.pop_back();
        }
    }

    void backtrackingGPT(const string& s, int start) {
        // 基线条件：如果起始位置等于字符串长度，说明找到了一种分割方式
        if (start == s.size()) {
            result.push_back(path);
            return;
        }

        // 递归切割
        for (int i = start + 1; i <= s.size(); i++) {
            string s_1 = s.substr(start, i - start);  // 从 start 到 i 的子字符串
            if (!isPalindrome(s_1)) {
                continue;
            }
            path.push_back(s_1);  // 将子串加入路径
            backtrackingGPT(s, i);  // 递归处理剩余部分
            path.pop_back();     // 回溯
        }
    }

    bool isPalindrome(string s) {
        for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;  // 空字符串也会被认为是回文
    }
};


int main() {
    Solution solution;

    string s = "abba";
    vector<vector<string>> result = solution.partition(s);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
