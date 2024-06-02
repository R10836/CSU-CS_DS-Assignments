# -*- coding: utf-8 -*-

"""
104. 二叉树的最大深度
简单
相关标签
相关企业
给定一个二叉树 root ，返回其最大深度。

二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。



示例 1：





输入：root = [3,9,20,null,null,15,7]
输出：3
示例 2：

输入：root = [1,null,2]
输出：2


提示：

树中节点的数量在 [0, 104] 区间内。
-100 <= Node.val <= 100
"""


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution(object):
    def build_binary_tree(self, node_value):
        if node_value is None:
            return None

        root = TreeNode(node_value[0])
        queue = [root]
        i = 1

        while i < len(node_value):
            current_node = queue.pop(0)

            left_value = node_value[i]
            i += 1
            if left_value is not None:
                current_node.left = TreeNode(left_value)
                queue.append(current_node.left)

            right_value = node_value[i]
            i += 1
            if right_value is not None:
                current_node.right = TreeNode(right_value)
                queue.append(current_node.right)

        return root

    def level_order_traversal(self, root):
        result = []
        if not root:
            return result

        queue = [root]

        while queue:
            current_node = queue.pop(0)
            result.append(current_node.value)

            if current_node.left:
                queue.append(current_node.left)
            if current_node.right:
                queue.append(current_node.right)

        return result

    def maxDepth(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """
        if not root:
            return 0

        left_depth = self.maxDepth(root.left)
        right_depth = self.maxDepth(root.right)

        return max(left_depth, right_depth) + 1


root = [3, 9, 20, None, None, 15, 7]
sol = Solution()
f = sol.build_binary_tree(root)
print(sol.maxDepth(f))
# if root.left is not None and root.right is not None:
#     deepest += 1
