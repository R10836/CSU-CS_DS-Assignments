#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 目录树节点
typedef struct TreeNode {
    char name[100];  // 目录名称
    struct TreeNode *parent;  // 父节点指针
    struct TreeNode *left;  // 左子节点指针
    struct TreeNode *right;  // 右子节点指针
} TreeNode;

// 创建新的目录树节点
TreeNode *createNewNode(const char *name) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    strcpy(newNode->name, name);
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 插入目录树节点
void insertNode(TreeNode *parent, TreeNode *child) {
    child->parent = parent;
    if (parent->left == NULL)
        parent->left = child;
    else
        parent->right = child;
}

// 查找目录树节点
TreeNode *findNode(TreeNode *root, const char *name) {
    if (root == NULL)
        return NULL;
    if (strcmp(root->name, name) == 0)
        return root;
    TreeNode *leftResult = findNode(root->left, name);
    if (leftResult != NULL)
        return leftResult;
    return findNode(root->right, name);
}

// 删除目录树节点
void deleteNode(TreeNode *node) {
    if (node == NULL)
        return;
    deleteNode(node->left);
    deleteNode(node->right);
    free(node);
}

// 建立目录
void createDirectory(TreeNode *root, const char *directoryName) {
    TreeNode *newNode = createNewNode(directoryName);
    insertNode(root, newNode);
    printf("目录创建成功\n");
}

// 修改目录结构
void moveDirectory(TreeNode *root, const char *directoryName, const char *newParentDirectory) {
    TreeNode *node = findNode(root, directoryName);
    if (node != NULL) {
        TreeNode *newParentNode = findNode(root, newParentDirectory);
        if (newParentNode != NULL) {
            // 将目录节点移动到新的父节点下
            if (node->parent != NULL) {
                if (node->parent->left == node)
                    node->parent->left = NULL;
                else
                    node->parent->right = NULL;
            }
            insertNode(newParentNode, node);
            printf("目录移动成功\n");
        } else {
            printf("父目录不存在\n");
        }
    } else {
        printf("目录不存在\n");
    }
}

// 查询目录
void findDirectory(TreeNode *root, const char *directoryName) {
    TreeNode *node = findNode(root, directoryName);
    if (node != NULL) {
        printf("目录存在\n");
    } else {
        printf("目录不存在\n");
    }
}

// 删除目录
void deleteDirectory(TreeNode *root, const char *directoryName) {
    TreeNode *node = findNode(root, directoryName);
    if (node != NULL) {
        deleteNode(node);
        printf("目录删除成功\n");
    } else {
        printf("目录不存在\n");
    }
}

int main() {
    TreeNode *root = createNewNode("root");

    // 测试建立目录
    createDirectory(root, "docs");

    // 测试修改目录结构
    moveDirectory(root, "docs", "documents");

    // 测试查询目录
    findDirectory(root, "documents");

    // 测试删除目录
    deleteDirectory(root, "documents");

    deleteNode(root);
    return 0;
}
