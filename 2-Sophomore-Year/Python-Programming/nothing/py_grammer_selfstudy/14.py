# -*- coding: utf-8 -*-

"""
14. 最长公共前缀
简单
相关标签
相关企业
编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。



示例 1：

输入：strs = ["flower","flow","flight"]
输出："fl"
示例 2：

输入：strs = ["dog","racecar","car"]
输出：""
解释：输入不存在公共前缀。


提示：

1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] 仅由小写英文字母组成
"""


class Solution(object):
    def longestCommonPrefix(self, strs):
        """
        :type strs: List[str]
        :rtype: str
        """
        answer = strs[0]
        for i in range(1, len(strs), 1):
            answer = self.compare_two(answer, strs[i])

        return answer

    def compare_two(self, str1, str2):
        """
        :param str1:
        :param str2:
        :return:
        """
        if len(str1) <= len(str2):
            shorter = str1
            longer = str2
        else:
            shorter = str2
            longer = str1

        temp = ""
        for i in range(0, len(shorter)):
            if shorter[i] == longer[i]:
                temp = temp + shorter[i]
            else:
                break

        return temp


sol = Solution()
strs = ["flower", "flow", "flight"]
print(sol.longestCommonPrefix(strs))
