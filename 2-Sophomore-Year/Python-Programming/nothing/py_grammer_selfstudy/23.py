# -*- coding: utf-8 -*-

"""
23. 合并 K 个升序链表
困难
相关标签
相关企业
给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。



示例 1：

输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6
示例 2：

输入：lists = []
输出：[]
示例 3：

输入：lists = [[]]
输出：[]


提示：

k == lists.length
0 <= k <= 10^4
0 <= lists[i].length <= 500
-10^4 <= lists[i][j] <= 10^4
lists[i] 按 升序 排列
lists[i].length 的总和不超过 10^4
"""


# Definition for singly-linked list.
class ListNode(object):
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution(object):
    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """
        temp_list = []
        for medium_list in lists:
            for item in medium_list:
                temp_list.append(item)
        temp_list.sort()
        # print(temp_list)
        return self.create_linklist(temp_list)

    def create_linklist(self, value_list):
        head = ListNode()
        current = head

        for value in value_list:
            current.next = ListNode(value)
            current = current.next

        return head.next

    def traverse_linklist(self, head):
        current = head
        while current is not None:
            print(current.val)
            current = current.next


sol = Solution()
lists = [[]]
sol.traverse_linklist(sol.mergeKLists(lists))
