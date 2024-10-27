//
// Created by Shawn33712 on 24-8-29.
//

/*
392. 判断子序列
简单
相关标签
相关企业
给定字符串 s 和 t ，判断 s 是否为 t 的子序列。

字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。

进阶：

如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？

致谢：

特别感谢 @pbrother 添加此问题并且创建所有测试用例。



示例 1：

输入：s = "abc", t = "ahbgdc"
输出：true
示例 2：

输入：s = "axc", t = "ahbgdc"
输出：false


提示：

0 <= s.length <= 100
0 <= t.length <= 10^4
两个字符串都只由小写字符组成。
*/

#include "iostream"
#include "string"
#include "vector"

using namespace std;


class Solution {
public:
    bool isSubsequence(string s, string t) {
        // 准备工作
        int sLen = s.size();
        int tLen = t.size();

        // dp
        vector<vector<int>> dp(sLen+1, vector<int>(tLen+1, 0));

        // 初始化

        // 递推公式
        for (int i = 1; i < sLen+1; i++) {
            for (int j = 1; j < tLen+1; j++) {
                if (s[i-1] == t[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        // 打印
        printDP(dp, sLen, tLen);

        // 返回
        return dp[sLen][tLen] == sLen;
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

    cout << boolalpha << solution.isSubsequence("abc", "ahbgdc") << endl;

    return 0;
}

//通过
//用时: 9 m 57 s
//Eastwood
//Eastwood
//提交于 2024.08.29 12:20
