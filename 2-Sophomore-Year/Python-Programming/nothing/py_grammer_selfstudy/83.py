# -*- coding: utf-8 -*-

"""
83. 删除排序链表中的重复元素
简单
相关标签
相关企业
给定一个已排序的链表的头 head ， 删除所有重复的元素，使每个元素只出现一次 。返回 已排序的链表 。



示例 1：


输入：head = [1,1,2]
输出：[1,2]
示例 2：


输入：head = [1,1,2,3,3]
输出：[1,2,3]


提示：

链表中节点数目在范围 [0, 300] 内
-100 <= Node.val <= 100
题目数据保证链表已经按升序 排列
"""


# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution(object):
    def deleteDuplicates(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """

        # The really core is considering the special case. Especially how to prevent viewing the 'None', because 'None' doesn't have any struct.

        if head is None:
            return None  # To prevent the case '[]'

        current = head

        while current.next is not None:  # All these options must be based on the struct 'ListNode', and it equals to prevent 'None'.
            compare = current.next.val
            while current.val == compare:
                current.next = current.next.next
                if current.next is not None:  # Bcause after upper options, the 'current.next' has changed, so we must be sure it still be 'ListNode'.
                    compare = current.next.val
                else:
                    break

            if current.next is not None:  # Bcause after upper options, the 'current.next' has changed, so we must be sure it still be 'ListNode'.
                current = current.next

        return head

    def create_linklist(self, value_list):
        """

        :param head:
        :return:
        """
        head = ListNode()
        current = head

        for val in value_list:
            current.next = ListNode(val)
            current = current.next

        return head.next  # 返回第一个有值的节点，之后第一个有值的节点都被当作头节点来用

    def traverse_linklist(self, head):
        """

        :param head:
        :return:
        """
        current = head
        while current is not None:
            print(current.val)
            current = current.next


sol = Solution()
value_list = [1, 1, 2, 3, 3]
sol.traverse_linklist(sol.deleteDuplicates(sol.create_linklist(value_list)))
