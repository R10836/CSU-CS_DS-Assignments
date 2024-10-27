#include <stdio.h>
#include <stdlib.h>

// �������ڵ�ṹ
typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// ��ȡ�����������
int getTreeDepth(TreeNode *root) {
    if (root == NULL)
        return 0;
    int leftDepth = getTreeDepth(root->left);
    int rightDepth = getTreeDepth(root->right);
    return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
}

// ��ӡ�������ṹ
void printBinaryTree(TreeNode *root, int depth) {
    if (root == NULL)
        return;
    printBinaryTree(root->right, depth + 1);  // ��ӡ���������Ϸ���
    printf("%*s%d\n", depth * 4, "", root->value);  // ��ӡ��ǰ�ڵ�
    printBinaryTree(root->left, depth + 1);  // ��ӡ���������·���
}

// �����������ڵ�
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
    // ����������ʾ��
    TreeNode *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    // ��ȡ���������
    int depth = getTreeDepth(root);

    // ��ӡ�������ṹ
    printf("���������ʽ�����ӡ�������ṹ��\n");
    printBinaryTree(root, depth);

    // �ͷ��ڴ�
    // ...

    return 0;
}