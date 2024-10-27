//
// Created by Shawn33712 on 24-8-18.
//

/*
144. 二叉树的前序遍历
简单
相关标签
相关企业
给你二叉树的根节点 root ，返回它节点值的 前序 遍历。



示例 1：


输入：root = [1,null,2,3]
输出：[1,2,3]
示例 2：

输入：root = []
输出：[]
示例 3：

输入：root = [1]
输出：[1]
示例 4：


输入：root = [1,2]
输出：[1,2]
示例 5：


输入：root = [1,null,2]
输出：[1,2]


提示：

树中节点数目在范围 [0, 100] 内
-100 <= Node.val <= 100


进阶：递归算法很简单，你可以通过迭代算法完成吗？
*/

#include "iostream"
#include "vector"
#include "queue"


using namespace std;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class MyBinaryTree {
private:
    TreeNode* root;

    void deleteTree(TreeNode* node) {
        if (node != nullptr) {
            deleteTree(node->left);   // 递归删除左子树
            deleteTree(node->right);  // 递归删除右子树
            delete node;              // 删除当前节点
        }
    }

public:
    MyBinaryTree() {
        root = nullptr;
    }

    ~MyBinaryTree() {
        deleteTree(root);  // 辅助函数，用于递归删除树的所有节点
    }

    void setRoot(int value) {
        if (root == nullptr) {
            root = new TreeNode(value);
        } else {
            root->val = value;
        }
    }

    TreeNode* getRoot() {
        return root;
    }

    void addChild(TreeNode* parent, int value, char way) {
        if (parent != nullptr) {
            if (way == 'l') {
                parent->left = new TreeNode(value);
            } else if (way == 'r') {
                parent->right = new TreeNode(value);
            } else {
                cout << "请输入 l 或者 r ！" << endl;
            }
        } else {
            cout << "父节点为空，无法添加子节点！" << endl;
        }
    }

    void preorderPrint(TreeNode* root) {
        // 基线
        if (root == nullptr) {
            return;
        }
        // 递归
        cout << root->val << "\t";
        preorderPrint(root->left);
        preorderPrint(root->right);
    }

    vector<int> preorderTraversal(TreeNode* root) {
        // 初始化
        vector<int> result;
        // 基线
        if (root == nullptr) {
            return result;
        }
        // 递归
        result.push_back(root->val);
        vector<int> tempLeft = preorderTraversal(root->left);
        result.insert(result.end(), tempLeft.begin(), tempLeft.end());
        vector<int> tempRight = preorderTraversal(root->right);
        result.insert(result.end(), tempRight.begin(), tempRight.end());
        // vector<int> 返回
        return result;
    }

    void inorderPrint(TreeNode* root) {
        // 基线
        if (root == nullptr) {
            return;
        }
        // 递归
        inorderPrint(root->left);
        cout << root->val << "\t";
        inorderPrint(root->right);
    }

    vector<int> inorderTraversal(TreeNode* root) {
        // 初始化
        vector<int> result;
        // 基线
        if (root == nullptr) {
            return result;
        }
        // 递归
        vector<int> tempLeft = inorderTraversal(root->left);
        result.insert(result.end(), tempLeft.begin(), tempLeft.end());

        result.push_back(root->val);

        vector<int> tempRight = inorderTraversal(root->right);
        result.insert(result.end(), tempRight.begin(), tempRight.end());

        // vector<int> 返回
        return result;
    }

    void postorderPrint(TreeNode* root) {
        // 基线
        if (root == nullptr) {
            return;
        }
        // 递归
        postorderPrint(root->left);
        postorderPrint(root->right);
        cout << root->val << "\t";
    }

    vector<int> postorderTraversal(TreeNode* root) {
        // 初始化
        vector<int> result;

        // 基线
        if (root == nullptr) {
            return result;
        }

        // 递归
        vector<int> tempLeft = postorderTraversal(root->left);
        result.insert(result.end(), tempLeft.begin(), tempLeft.end());

        vector<int> tempRight = postorderTraversal(root->right);
        result.insert(result.end(), tempRight.begin(), tempRight.end());

        result.push_back(root->val);

        // vector<int> 返回
        return result;
    }

    void levelOrderPrint(TreeNode* root) {
        // 初始化
        queue<TreeNode*> q;
        // 特殊情况
        if (root == nullptr) {
            return;
        }
        // 头
        q.push(root);
        // 遍历
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            cout << node->val << "\t";
            if (node->left != nullptr) {
                q.push(node->left);
            }
            if (node->right != nullptr) {
                q.push(node->right);
            }
        }
    }

    vector<vector<int>> levelOrderTraversal(TreeNode* root) {
        // 初始化
        vector<int> subResult;
        vector<vector<int>> result;
        queue<TreeNode*> q;
        TreeNode* lineEndFlag = root;  // 标注行末尾节点的指针
        TreeNode* tempFlag;  // 标注当前遍历最远的那个节点的指针

        // 特殊情况
        if (root == nullptr) {
            return result;
        }

        // 头
        q.push(root);
        subResult.push_back(q.front()->val);
        result.push_back(subResult);
        subResult.clear();

        // 遍历
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();

            if (current->left != nullptr) {
                tempFlag = current->left;
                q.push(tempFlag);
                subResult.push_back(tempFlag->val);
            }
            if (current->right != nullptr) {
                tempFlag = current->right;
                q.push(tempFlag);
                subResult.push_back(tempFlag->val);
            }

            if (current == lineEndFlag){
                result.push_back(subResult);
                subResult.clear();
                lineEndFlag = tempFlag;
            }
        }

        // 返回
        result.pop_back();  // 最后多了一个空的subResult
        return result;
    }

    vector<vector<int>> levelOrderTraversalGPT(TreeNode* root) {
        // 初始化
        vector<vector<int>> result;
        queue<TreeNode*> q;

        // 特殊情况
        if (root == nullptr) {
            return result;
        }

        // 头
        q.push(root);

        // 遍历
        while (!q.empty()) {
            vector<int> subResult;
            int levelSize = q.size();  // 当前层的节点数，即队列中所有待处理的节点数量

            for (int i = 0; i < levelSize; i++) {  // 遍历当前层的所有节点
                TreeNode* current = q.front();
                q.pop();
                subResult.push_back(current->val);

                if (current->left != nullptr) {
                    q.push(current->left);
                }
                if (current->right != nullptr) {
                    q.push(current->right);
                }
            }
            result.push_back(subResult);
        }

        // 返回
        return result;
    }
};


int main() {
    MyBinaryTree tree;

    tree.setRoot(888);
    TreeNode* root = tree.getRoot();

    tree.addChild(root, 10, 'l');
    tree.addChild(root, 11, 'r');
    tree.addChild(root->left, 21, 'l');
    tree.addChild(root->left, 22, 'r');
    tree.addChild(root->right, 23, 'l');
    tree.addChild(root->right, 24, 'r');
    tree.addChild(root->left->left, 31, 'r');
    tree.addChild(root->left->right, 32, 'l');
    tree.addChild(root->right->left, 33, 'l');
    tree.addChild(root->right->right, 34, 'r');

    tree.preorderPrint(root);
    cout << endl;
    tree.inorderPrint(root);
    cout << endl;
    tree.postorderPrint(root);
    cout << endl;
    tree.levelOrderPrint(root);
    cout << endl;

    return 0;
}
