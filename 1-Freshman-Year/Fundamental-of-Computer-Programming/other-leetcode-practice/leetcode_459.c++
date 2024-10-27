//
// Created by Shawn33712 on 24-8-17.
//

/*
459. 重复的子字符串
简单
相关标签
相关企业
给定一个非空的字符串 s ，检查是否可以通过由它的一个子串重复多次构成。



示例 1:

输入: s = "abab"
输出: true
解释: 可由子串 "ab" 重复两次构成。
示例 2:

输入: s = "aba"
输出: false
示例 3:

输入: s = "abcabcabcabc"
输出: true
解释: 可由子串 "abc" 重复四次构成。 (或子串 "abcabc" 重复两次构成。)


提示：

1 <= s.length <= 104
s 由小写英文字母组成
*/

#include "iostream"
#include "string"

using namespace std;


class Solution {
public:
    bool repeatedSubstringPatternViolent(string s) {
        // O(n^2)
        int pos = -1;
        int j = 0;

        for (int i = 1; i < s.size(); i++) {
            if (pos == -1){
                if (s[i] == s[0]) {
                    pos = i - 1;
                    i--;  // 为了相当于i没动
                }
            } else {
                if (s[i] == s[j]) {
                    if (j == pos) {
                        j = 0;
                        if (i == s.size() - 1) {
                            return true;
                        }
                    } else {
                        j++;
                    }
                } else {
                    i = pos + 1;
                    j = 0;
                    pos = -1;
                }
            }
        }

        return false;
    }

    bool repeatedSubstringPattern(string s) {
        // KMP
        // O(n)
        int* next = writeNEXT(s);
        int len = s.size();
        int biggestSubNum = next[len - 1];

        if (biggestSubNum != 0 && len % (len - biggestSubNum) == 0) {
            delete[] next; return true;
        }
        delete[] next; return false;
    }

    int* writeNEXT(string s) {
        int len = s.size();
        int* next = new int[len];

        // 1 初始化
        next[0] = 0;
        int j = 0, i = 1;  // j: 指向前缀的最后一个元素。 i: 指向后缀的最后一个元素。
        for (; i < s.size(); i++) {

            // 2 前后缀不相同时
            while (j > 0 && s[i] != s[j]) {
                j = next[j - 1];
            }

            // 3 前后缀相同时
            if (s[i] == s[j]) {
                j++;
            }

            // 4 更新next
            next[i] = j;
        }

        return next;
    }
};


int main() {
    Solution sol;

    string s = "abac";

//    cout << boolalpha << sol.repeatedSubstringPatternViolent(s) << endl;
    cout << boolalpha << sol.repeatedSubstringPattern(s) << endl;

    return 0;
}
