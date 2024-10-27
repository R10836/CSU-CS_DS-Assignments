//
// Created by Shawn33712 on 24-7-23.
//
/*
206. 反转链表
已解答
简单
相关标签
相关企业
给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。


示例 1：


输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
示例 2：


输入：head = [1,2]
输出：[2,1]
示例 3：

输入：head = []
输出：[]


提示：

链表中节点的数目范围是 [0, 5000]
-5000 <= Node.val <= 5000


进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？
*/
#include "iostream"
#include "vector"
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
private:
    ListNode* head;

public:
    Solution() : head() {}

    ~Solution() {
        ListNode* current = head;
        ListNode* next;
        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }
    }

    ListNode* getHead() {
        return head;
    }

    void insert(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = head;
        head = newNode;
    }

    void travel(ListNode* from_here) {
        ListNode* current = from_here;
        while (current != nullptr) {
            cout << current->val << " --> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }

    ListNode* reverseList(ListNode* old_head) {
        //执行用时分布
        //9
        //ms
        //击败
        //6.85%
        ListNode* reversed_head = new ListNode();
        ListNode* current = old_head;
        ListNode* current_copy;

        while (current != nullptr) {
            current_copy = current;
            current = current->next;

            current_copy->next = reversed_head->next;
            reversed_head->next = current_copy;
        }

        return reversed_head->next;
    }

    ListNode* reverseListGPT(ListNode* old_head) {
        //执行用时分布
        //3
        //ms
        //击败
        //81.80%
        ListNode* prev = nullptr;
        ListNode* current = old_head;

        while (current != nullptr) {
            ListNode* nxt = current->next;
            current->next = prev;
            prev = current;
            current = nxt;
        }

        return prev;
    }
};

int main() {
    vector<int> input_list1 = {};
    vector<int> input_list2 = {1, 2};
    vector<int> input_list3 = {1, 2, 3, 4, 5};

    Solution sol1;
    Solution sol2;
    Solution sol3;

    for (const auto& elem : input_list1) {
        sol1.insert(elem);
    }
    for (const auto& elem : input_list2) {
        sol2.insert(elem);
    }
    for (const auto& elem : input_list3) {
        sol3.insert(elem);
    }

    sol1.travel(sol1.getHead());
    sol2.travel(sol2.getHead());
    sol3.travel(sol3.getHead());
    cout << "=============" << endl;

//    sol1.travel(sol1.reverseList(sol1.getHead()));
//    sol2.travel(sol2.reverseList(sol2.getHead()));
//    sol3.travel(sol3.reverseList(sol3.getHead()));
//    cout << "=============" << endl;
//    sol1.travel(sol1.getHead());
//    sol2.travel(sol2.getHead());
//    sol3.travel(sol3.getHead());
//    cout << "=============" << endl;

    sol1.travel(sol1.reverseListGPT(sol1.getHead()));
    sol2.travel(sol2.reverseListGPT(sol2.getHead()));
    sol3.travel(sol3.reverseListGPT(sol3.getHead()));
    cout << "=============" << endl;
    sol1.travel(sol1.getHead());
    sol2.travel(sol2.getHead());
    sol3.travel(sol3.getHead());
    cout << "=============" << endl;
    // 反转链表函数在操作过程中会修改原始链表节点的指针，这导致原始链表结构被破坏。这是因为链表的反转操作是通过改变每个节点的 next 指针来实现的，所以原链表的结构会被更改。
}
