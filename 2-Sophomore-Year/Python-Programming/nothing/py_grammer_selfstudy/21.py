# -*- coding: utf-8 -*-

"""
21. 合并两个有序链表
简单
相关标签
相关企业
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。



示例 1：


输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
示例 2：

输入：l1 = [], l2 = []
输出：[]
示例 3：

输入：l1 = [], l2 = [0]
输出：[0]


提示：

两个链表的节点数目范围是 [0, 50]
-100 <= Node.val <= 100
l1 和 l2 均按 非递减顺序 排列
"""


# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution(object):
    def create_linklist(self, elem_list):
        head = ListNode()
        current = head

        for elem in elem_list:
            current.next = ListNode(elem)
            current = current.next

        return head.next

    def traverse(self, linklist):
        current = linklist
        while current is not None:
            print(current.val)
            current = current.next

    def mergeTwoLists(self, list1, list2):
        """
        :type list1: Optional[ListNode]
        :type list2: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        if list1 is not None and list2 is not None:
            if list2.val <= list1.val:
                down = list2
                upon = list1
            else:
                down = list1
                upon = list2

            chosen = down
            while down.next is not None:
                if upon is None:
                    return chosen
                else:
                    if down.val <= upon.val <= down.next.val:
                        p = upon
                        upon = upon.next
                        p.next = down.next
                        down.next = p
                        down = down.next
                    elif down.next.val < upon.val:
                        down = down.next

            down.next = upon

            return chosen

        elif list1 is None and list2 is not None:
            return list2

        elif list1 is not None and list2 is None:
            return list1

        else:
            return None


sol = Solution()
l1 = [7, 17, 18]
l2 = [1, 5, 10, 15, 90, 111]

sol.traverse(sol.mergeTwoLists(sol.create_linklist(l1), sol.create_linklist(l2)))
