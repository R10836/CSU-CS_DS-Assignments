#include <stdio.h>
#include <stdlib.h>

// 二叉树节点结构
typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 获取二叉树的深度
int getTreeDepth(TreeNode *root) {
    if (root == NULL)
        return 0;
    int leftDepth = getTreeDepth(root->left);
    int rightDepth = getTreeDepth(root->right);
    return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
}

// 打印二叉树结构
void printBinaryTree(TreeNode *root, int depth) {
    if (root == NULL)
        return;
    printBinaryTree(root->right, depth + 1);  // 打印右子树（上方）
    printf("%*s%d\n", depth * 4, "", root->value);  // 打印当前节点
    printBinaryTree(root->left, depth + 1);  // 打印左子树（下方）
}

// 创建二叉树节点
TreeNode* createNode(int value) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode != NULL) {
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

int main() {
    // 创建二叉树示例
    TreeNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // 获取二叉树深度
    int depth = getTreeDepth(root);

    // 打印二叉树结构
    printf("按凹入表形式横向打印二叉树结构：\n");
    printBinaryTree(root, depth);

    // 释放内存
    // ...

    return 0;
}