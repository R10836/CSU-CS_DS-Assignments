# -*- coding: utf-8 -*-


"""
2. 两数相加
中等
相关标签
相关企业
给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。



示例 1：


输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[7,0,8]
解释：342 + 465 = 807.
示例 2：

输入：l1 = [0], l2 = [0]
输出：[0]
示例 3：

输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
输出：[8,9,9,9,0,0,0,1]


提示：

每个链表中的节点数在范围 [1, 100] 内
0 <= Node.val <= 9
题目数据保证列表表示的数字不含前导零
"""


# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution(object):
    def create_linked_list(self, values):
        head = ListNode()  # 创建一个虚拟头结点
        current = head

        for val in values:
            current.next = ListNode(val)
            current = current.next

        return head.next  # 返回真正的头结点

    def create_linked_list_2(self, values):
        head = ListNode()  # 创建一个虚拟头结点
        current = head

        for val in reversed(values):
            current.next = ListNode(val)
            current = current.next

        return head.next  # 返回真正的头结点

    def addTwoNumbers(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """
        num1 = 0
        num2 = 0
        i = 0
        j = 0

        p = l1
        while p is not None:
            num1 += p.val * pow(10, i)
            i += 1
            p = p.next

        q = l2
        while q is not None:
            num2 += q.val * pow(10, j)
            j += 1
            q = q.next

        sum_list = list(str(num1 + num2))
        # for i in sum_str:
        #     print(i)
        return self.create_linked_list_2(sum_list)


# 定义链表节点的值
l1_values = [9, 9, 9, 9, 9, 9, 9]
l2_values = [9, 9, 9, 9]

sol = Solution()
# 创建l1和l2链表
l1 = sol.create_linked_list(l1_values)
l2 = sol.create_linked_list(l2_values)
print(sol.addTwoNumbers(l1, l2))

"""
class Solution(object):
    def create_linked_list_2(self, values):
        head = ListNode()  # 创建一个虚拟头结点
        current = head

        for val in reversed(values):
            current.next = ListNode(val)
            current = current.next

        return head.next  # 返回真正的头结点

    def addTwoNumbers(self, l1, l2):
        num1 = 0
        num2 = 0
        i = 0
        j = 0

        p = l1
        while p is not None:
            num1 += p.val * pow(10, i)
            i += 1
            p = p.next

        q = l2
        while q is not None:
            num2 += q.val * pow(10, j)
            j += 1
            q = q.next

        sum_list = list(str(num1 + num2))
        # for i in sum_str:
        #     print(i)
        return self.create_linked_list_2(sum_list)
"""
