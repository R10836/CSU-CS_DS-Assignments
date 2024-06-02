# -*- coding: utf-8 -*-

"""
993. 二叉树的堂兄弟节点
简单
相关标签
相关企业
在二叉树中，根节点位于深度 0 处，每个深度为 k 的节点的子节点位于深度 k+1 处。

如果二叉树的两个节点深度相同，但 父节点不同 ，则它们是一对堂兄弟节点。

我们给出了具有唯一值的二叉树的根节点 root ，以及树中两个不同节点的值 x 和 y 。

只有与值 x 和 y 对应的节点是堂兄弟节点时，才返回 true 。否则，返回 false。



示例 1：


输入：root = [1,2,3,4], x = 4, y = 3
输出：false
示例 2：


输入：root = [1,2,3,null,4,null,5], x = 5, y = 4
输出：true
示例 3：



输入：root = [1,2,3,null,4], x = 2, y = 3
输出：false


提示：

二叉树的节点数介于 2 到 100 之间。
每个节点的值都是唯一的、范围为 1 到 100 的整数。
"""


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution(object):
    def level_order_build(self, node_value):
        """
        层序建立二叉树
        :param node_value: 层序值的列表
        :return: root: 根节点
        """
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
        """
        层序遍历二叉树
        :param root: 根节点
        :return: result: 层序值的列表
        """
        result = []
        if not root:
            return result

        queue = [root]

        while queue:
            current_node = queue.pop(0)
            result.append(current_node.val)

            if current_node.left:
                queue.append(current_node.left)
            if current_node.right:
                queue.append(current_node.right)

        return result

    def isCousins(self, root, x, y):
        """
        Written by ChatGPT!

        判断两个节点是否为堂兄弟节点
        :param root: 二叉树的根节点
        :param x: 节点x的值
        :param y: 节点y的值
        :return: 如果是堂兄弟节点，返回True；否则返回False
        """

        def find_depth_and_parent(node, target, depth, parent):
            if node is None:
                return None

            if node.val == target:
                return (depth, parent)

            left_result = find_depth_and_parent(node.left, target, depth + 1, node)
            right_result = find_depth_and_parent(node.right, target, depth + 1, node)

            return left_result or right_result

        x_info = find_depth_and_parent(root, x, 0, None)
        y_info = find_depth_and_parent(root, y, 0, None)

        if x_info is not None and y_info is not None:
            x_depth, x_parent = x_info
            y_depth, y_parent = y_info

            return x_depth == y_depth and x_parent != y_parent
        else:
            return False


sol = Solution()
root = [1, 2, 3, None, 4]
x = 2
y = 3
tree = sol.level_order_build(root)
print(sol.level_order_traversal(tree))
print(sol.isCousins(tree, x, y))
