//
// Created by Shawn33712 on 24-8-16.
//

/*
28. 找出字符串中第一个匹配项的下标
已解答
简单
相关标签
相关企业
给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。如果 needle 不是 haystack 的一部分，则返回  -1 。



示例 1：

输入：haystack = "sadbutsad", needle = "sad"
输出：0
解释："sad" 在下标 0 和 6 处匹配。
第一个匹配项的下标是 0 ，所以返回 0 。
示例 2：

输入：haystack = "leetcode", needle = "leeto"
输出：-1
解释："leeto" 没有在 "leetcode" 中出现，所以返回 -1 。


提示：

1 <= haystack.length, needle.length <= 104
haystack 和 needle 仅由小写英文字符组成
*/

#include "iostream"
#include "string"

using namespace std;


class Solution {
public:
    int strStr(string haystack, string needle) {
        int* next = writeNEXT(needle);

        int j = 0;
        for (int i = 0; i < haystack.size(); i++) {
            while (j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j]) {
                j++;
            }

            if (j == needle.size()) {
                delete[] next;  // !!! 记得在使用完后释放内存
                return i - needle.size() + 1;
            }
        }

        delete[] next;  // !!! 记得在使用完后释放内存
        return -1;
    }

    int* writeNEXT(string needle) {
        // 1 初始化
        int len = needle.size();
        int* next = new int[len];

        next[0] = 0;
        int j = 0, i = 1;  // j: 指向前缀的最后一个元素。 i: 指向后缀的最后一个元素。

        for (; i < len; i++) {
            while (j > 0 && needle[i] != needle[j]) {  // 2 前后缀不相同时
                j = next[j - 1];
            }
            if (needle[i] == needle[j]) {  // 3 前后缀相同时
                j++;
            }

            next[i] = j;  // 4 更新next
        }

        return next;  // 返回指向数组的指针
    }
};


int main() {
    Solution sol;

    string haystack = "sadbutsad";
    string needle = "sad";

    cout << sol.strStr(haystack, needle) << endl;

    return 0;
}
