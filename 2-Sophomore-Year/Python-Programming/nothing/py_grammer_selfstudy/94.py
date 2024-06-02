# -*- coding: utf-8 -*-

"""
94. 二叉树的中序遍历
简单
相关标签
相关企业
给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。



示例 1：


输入：root = [1,null,2,3]
输出：[1,3,2]
示例 2：

输入：root = []
输出：[]
示例 3：

输入：root = [1]
输出：[1]


提示：

树中节点数目在范围 [0, 100] 内
-100 <= Node.val <= 100


进阶: 递归算法很简单，你可以通过迭代算法完成吗？
"""


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution(object):
    # 中序遍历
    def inorderTraversal(self, root: TreeNode):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        traversal_list = []

        if root is None:
            return traversal_list

        self.inorderTraversal(root.left)
        traversal_list.append(root.val)
        self.inorderTraversal(root.right)

        return traversal_list

    # 先序建立
    def create_tree(self, root: TreeNode, val_list: list):
        """

        :param root:
        :param val_list:
        :return:
        """
        if not val_list:
            root = None
            return root

        if val_list[0] is None:
            val_list.append(0)
            root = None
            return root
        else:
            root.val = val_list.append(0)
            root.left = self.create_tree(root.left, val_list)
            root.right = self.create_tree(root.right, val_list)
            return root


sol = Solution()
root1 = TreeNode()
vals = [1, None, 2, 3]

print(sol.inorderTraversal(sol.create_tree(root1, vals)))


"""
# -*- coding: utf-8 -*-

# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution(object):
    # 中序遍历
    def inorderTraversal(self, root: TreeNode):
        traversal_list = []

        def inorder_helper(node):
            if node is not None:
                inorder_helper(node.left)
                traversal_list.append(node.val)
                inorder_helper(node.right)

        inorder_helper(root)
        return traversal_list

    # 先序建立
    def create_tree(self, val_list: list):
        if not val_list:
            return None

        root_val = val_list.pop(0)
        if root_val is None:
            return None

        root = TreeNode(val=root_val)
        root.left = self.create_tree(val_list)
        root.right = self.create_tree(val_list)
        return root


sol = Solution()
vals = [1, None, 2, 3]
root1 = sol.create_tree(vals)
print(sol.inorderTraversal(root1))

"""