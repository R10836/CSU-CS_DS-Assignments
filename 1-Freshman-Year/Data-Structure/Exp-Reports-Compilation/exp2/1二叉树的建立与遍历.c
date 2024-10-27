#include <stdio.h>
#include <stdlib.h>

// ��������㶨��
typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

// ������㺯��
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ��������������
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

// �����������
void preorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%c", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// �����������
void inorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%c", root->data);
    inorderTraversal(root->right);
}

// �����������
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

    printf("�������ݣ�[");
    printf(preorder);
    printf("]\n");

    Node* root = buildTree(preorder, &index);

    printf("������������");
    preorderTraversal(root);
    printf("\n");

    printf("������������");
    inorderTraversal(root);
    printf("\n");

    printf("������������");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
