//
// Created by Shawn33712 on 24-9-3.
//

/*
516. 最长回文子序列
中等
相关标签
相关企业
给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。

子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。



示例 1：

输入：s = "bbbab"
输出：4
解释：一个可能的最长回文子序列为 "bbbb" 。
示例 2：

输入：s = "cbbd"
输出：2
解释：一个可能的最长回文子序列为 "bb" 。


提示：

1 <= s.length <= 1000
s 仅由小写英文字母组成
*/

#include "iostream"
#include "vector"

using namespace std;


class Solution {
public:
    int longestPalindromeSubseq(string s) {
        // 准备工作
        int len = s.size();

        // dp
        vector<vector<int>> dp(len, vector<int> (len, 0));

        // 初始化
        for (int k = 0; k < len; k++) {
            dp[k][k] = 1;
        }

        // 递推公式
        for (int j = 1; j < len; j++) {
            for (int i = j-1; i >= 0; i--) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i+1][j-1] + 2;
                } else {
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }
            }
        }

        // 打印
        printDP(dp, len-1, len-1);

        // 返回
        return dp[0][len-1];
    }

    void printDP(vector<vector<int>>& dp, int iMax, int jMax) {
        // 数组最后一个元素为dp[iMax][jMax]
        for (int i = 0; i <= iMax; i++) {
            for (int j = 0; j <= jMax; j++) {
                cout << dp[i][j] << "\t";
            }
            cout << endl;
        }
    }
};


int main() {
    Solution solution;

    string s = "bbbab";
    cout << solution.longestPalindromeSubseq(s) << endl;

    return 0;
}
