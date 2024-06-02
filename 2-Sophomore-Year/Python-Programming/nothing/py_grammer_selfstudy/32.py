# -*- coding: utf-8 -*-

"""
32. 最长有效括号
困难
相关标签
相关企业
给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。



示例 1：

输入：s = "(()"
输出：2
解释：最长有效括号子串是 "()"
示例 2：

输入：s = ")()())"
输出：4
解释：最长有效括号子串是 "()()"
示例 3：

输入：s = ""
输出：0


提示：

0 <= s.length <= 3 * 104
s[i] 为 '(' 或 ')'
"""

"""
# 题目没有描述清楚自己的需求。。。
list_s = list(s)  # 无脑转换成列表先
count = 0
max_count = 0
flag = 0

for index in list_s:
    if index == '(':
        if flag == 1:
            pass
        else:
            count = 0
        flag = -1
    elif index == ')':
        if flag == -1:
            count += 2
            # print(count)
        else:
            count = 0
        flag = 1
    if max_count < count:
        max_count = count

return max_count
"""


# 正文：
class Solution:
    def longest_valid_parentheses(self, s):
        list_s = list(s)
        original = []
        live = []
        switch = []

        if not list_s:
            return 0

        for index in range(len(list_s)):
            original.append(Combine(elem=list_s[index], rank=index, state=0))

        for index in range(0, len(list_s)):
            if not live:
                live.append(original[index])
            else:
                live.append(original[index])
                if live[-1].elem == ')':
                    if live[-2].elem == '(':
                        switch.append(live[-2].rank)
                        switch.append(live[-1].rank)
                        live.pop()
                        live.pop()

        # for item in live:
        #     print(item.elem, item.rank, item.state)

        print(sorted(switch))
        final_switch = sorted(switch)
        count = 0
        max_count = 0
        for index in range(0, len(final_switch) - 1):
            if final_switch[index] == final_switch[index + 1] - 1:
                count += 1
            else:
                count = 0
            if max_count < count:
                max_count = count

        if max_count > 0:
            max_count += 1

        return max_count


class Combine:
    def __init__(self, elem, rank, state):
        self.elem = elem
        self.rank = rank
        self.state = state


sol = Solution()
ss = "()(()"
print(sol.longest_valid_parentheses(ss))
