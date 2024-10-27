#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ŀ¼���ڵ�
typedef struct TreeNode {
    char name[100];  // Ŀ¼����
    struct TreeNode *parent;  // ���ڵ�ָ��
    struct TreeNode *left;  // ���ӽڵ�ָ��
    struct TreeNode *right;  // ���ӽڵ�ָ��
} TreeNode;

// �����µ�Ŀ¼���ڵ�
TreeNode *createNewNode(const char *name) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    strcpy(newNode->name, name);
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ����Ŀ¼���ڵ�
void insertNode(TreeNode *parent, TreeNode *child) {
    child->parent = parent;
    if (parent->left == NULL)
        parent->left = child;
    else
        parent->right = child;
}

// ����Ŀ¼���ڵ�
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

// ɾ��Ŀ¼���ڵ�
void deleteNode(TreeNode *node) {
    if (node == NULL)
        return;
    deleteNode(node->left);
    deleteNode(node->right);
    free(node);
}

// ����Ŀ¼
void createDirectory(TreeNode *root, const char *directoryName) {
    TreeNode *newNode = createNewNode(directoryName);
    insertNode(root, newNode);
    printf("Ŀ¼�����ɹ�\n");
}

// �޸�Ŀ¼�ṹ
void moveDirectory(TreeNode *root, const char *directoryName, const char *newParentDirectory) {
    TreeNode *node = findNode(root, directoryName);
    if (node != NULL) {
        TreeNode *newParentNode = findNode(root, newParentDirectory);
        if (newParentNode != NULL) {
            // ��Ŀ¼�ڵ��ƶ����µĸ��ڵ���
            if (node->parent != NULL) {
                if (node->parent->left == node)
                    node->parent->left = NULL;
                else
                    node->parent->right = NULL;
            }
            insertNode(newParentNode, node);
            printf("Ŀ¼�ƶ��ɹ�\n");
        } else {
            printf("��Ŀ¼������\n");
        }
    } else {
        printf("Ŀ¼������\n");
    }
}

// ��ѯĿ¼
void findDirectory(TreeNode *root, const char *directoryName) {
    TreeNode *node = findNode(root, directoryName);
    if (node != NULL) {
        printf("Ŀ¼����\n");
    } else {
        printf("Ŀ¼������\n");
    }
}

// ɾ��Ŀ¼
void deleteDirectory(TreeNode *root, const char *directoryName) {
    TreeNode *node = findNode(root, directoryName);
    if (node != NULL) {
        deleteNode(node);
        printf("Ŀ¼ɾ���ɹ�\n");
    } else {
        printf("Ŀ¼������\n");
    }
}

int main() {
    TreeNode *root = createNewNode("root");

    // ���Խ���Ŀ¼
    createDirectory(root, "docs");

    // �����޸�Ŀ¼�ṹ
    moveDirectory(root, "docs", "documents");

    // ���Բ�ѯĿ¼
    findDirectory(root, "documents");

    // ����ɾ��Ŀ¼
    deleteDirectory(root, "documents");

    deleteNode(root);
    return 0;
}
