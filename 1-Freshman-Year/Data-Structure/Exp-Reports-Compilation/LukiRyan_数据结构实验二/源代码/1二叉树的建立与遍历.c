#include <stdio.h>
#include <stdlib.h>

// 二叉树结点定义
typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

// 创建结点函数
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 构建二叉树函数
Node* buildTree(char* preorder, int* index) {
    if (preorder[*index] == '\0' || preorder[*index] == ' ') {
        (*index)++;
        return NULL;
    }

    Node* node = createNode(preorder[*index]);
    (*index)++;
    node->left = buildTree(preorder, index);
    node->right = buildTree(preorder, index);
    return node;
}

// 先序遍历函数
void preorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%c", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// 中序遍历函数
void inorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%c", root->data);
    inorderTraversal(root->right);
}

// 后序遍历函数
void postorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%c", root->data);
}

int main() {
    char preorder[] = "ABC  DE G  F   ";
    int index = 0;

    printf("测试数据：[");
    printf(preorder);
    printf("]\n");

    Node* root = buildTree(preorder, &index);

    printf("先序遍历结果：");
    preorderTraversal(root);
    printf("\n");

    printf("中序遍历结果：");
    inorderTraversal(root);
    printf("\n");

    printf("后序遍历结果：");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
