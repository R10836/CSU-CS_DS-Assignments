//
// Created by Shawn33712 on 24-9-3.
//

/*
5. 最长回文子串
中等
相关标签
相关企业
提示
给你一个字符串 s，找到 s 中最长的
回文

子串
。



示例 1：

输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。
示例 2：

输入：s = "cbbd"
输出："bb"


提示：

1 <= s.length <= 1000
s 仅由数字和英文字母组成

*/

#include "iostream"
#include "string"
#include "vector"

using namespace std;


class Solution {
public:
    string longestPalindrome(string s) {
        // 准备工作
        int len = s.size();
        int maxSub = 1, start = len-1;

        // DP
        vector<vector<bool>> dp(len, vector<bool>(len, true));

        // 初始化
        for (int k = 0; k < len; k++) {
            dp[k][k] = true;
        }

        // 递推公式
        for (int j = 1; j < len; j++) {
            for (int i = j-1; i >= 0; i--) {
                if (s[i] == s[j] && dp[i+1][j-1]) {
                    dp[i][j] = true;
                    if ((j-i+1) > maxSub) {
                        maxSub = j - i + 1;
                        start = i;
                    }
                } else {
                    dp[i][j] = false;
                }
            }
        }

        // 打印
        printDP(dp, len-1, len-1);
        cout << start << " " << maxSub << endl;

        // 返回
        return s.substr(start, maxSub);
    }

    void printDP(vector<vector<bool>>& dp, int iMax, int jMax) {
        // 数组最后一个元素为dp[iMax][jMax]
        for (int i = 0; i <= iMax; i++) {
            for (int j = 0; j <= jMax; j++) {
                cout << boolalpha << dp[i][j] << "\t";
            }
            cout << endl;
        }
    }
};


int main() {
    Solution solution;

    string s = "avoa";
    cout << solution.longestPalindrome(s) << endl;

    return 0;
}