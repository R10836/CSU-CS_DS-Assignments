# -*- coding: utf-8 -*-

"""
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
每个右括号都有一个对应的相同类型的左括号。


示例 1：

输入：s = "()"
输出：true
示例 2：

输入：s = "()[]{}"
输出：true
示例 3：

输入：s = "(]"
输出：false


提示：

1 <= s.length <= 104
s 仅由括号 '()[]{}' 组成
"""


class Solution(object):
    def __init__(self):
        self.stack = []  # 建立空列表，而不是空字符串

    def is_valid(self, s):
        """
        :type s: str
        :rtype: bool
        """
        list_s = list(s)
        # print(list_s)

        for item in list_s:
            if item in ['[', '{', '(']:
                self.push(item)
            elif item in [']', '}', ')']:
                if not self.stack:
                    return False
                else:
                    if item == ']' and self.stack[-1] == '[':
                        self.pop()
                        continue
                    elif item == '}' and self.stack[-1] == '{':
                        self.pop()
                        continue
                    elif item == ')' and self.stack[-1] == '(':
                        self.pop()
                        continue
                    else:
                        # print(self.stack, self.stack[-1])
                        return False
        if not self.stack:
            return True
        else:
            return False

    def push(self, item):
        self.stack.append(item)
        # print(item, 'is pushed')

    def pop(self):
        if self.stack:
            # print('_ is poped')
            return self.stack.pop()
        else:
            return None


sol = Solution()
s = "(])"
print(sol.is_valid(s))
