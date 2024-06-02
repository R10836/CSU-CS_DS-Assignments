# -*- coding: utf-8 -*-

"""
3. 无重复字符的最长子串
中等
相关标签
相关企业
给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。



示例 1:

输入: s = "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:

输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:

输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。


提示：

0 <= s.length <= 5 * 104
s 由英文字母、数字、符号和空格组成
"""


class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        s2 = ''
        length = 0
        max_length = 0

        for i in s:
            if i in s2:
                for j in s2:
                    if j == i:
                        s2 = s2[s2.index(i) + 1:] + i
                        length = len(s2)
                        break
                if max_length < length:
                    max_length = length
            else:
                s2 += i
                length += 1
                if max_length < length:
                    max_length = length

            # print(s2, length, max_length)

        return max_length


sol = Solution()
s = "dvdf"
print(sol.lengthOfLongestSubstring(s))

