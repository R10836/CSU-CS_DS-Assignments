# -*- coding: utf-8 -*-

"""
给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。



示例 1：


输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
示例 2：

输入：head = [1], n = 1
输出：[]
示例 3：

输入：head = [1,2], n = 1
输出：[1]


提示：

链表中结点的数目为 sz
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz


进阶：你能尝试使用一趟扫描实现吗？
"""


# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution(object):
    def create_linklist(self, values):
        head = ListNode()
        current = head

        for val in values:
            current.next = ListNode(val)
            current = current.next

        return head.next  # 也可以返回第一个有值的节点head.next，但这里返回的是头节点head
        # 但他妈LeetCode默认返回的是head.next

    def traverse_linklist(self, head):
        current = head

        while current is not None:
            print(current.val)

            current = current.next

    def removeNthFromEnd(self, head, n):
        """
        :type head: ListNode
        :type n: int
        :rtype: ListNode
        """
        count = 1

        current = head
        while current.next is not None:
            current = current.next
            count += 1
        # print('count is:', count)

        current = head
        if (count - n - 1) == -1:
            head = current.next
        else:
            for i in range(count - n - 1):
                current = current.next
            current.next = current.next.next

        return head


sol = Solution()
vals = [1, 2, 3, 4, 5]
n = 2
l1 = sol.create_linklist(vals)
sol.traverse_linklist(sol.removeNthFromEnd(l1, n))
