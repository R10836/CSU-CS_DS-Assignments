//
// Created by Shawn33712 on 24-8-16.
//

/*
707. 设计链表
中等
相关标签
相关企业
你可以选择使用单链表或者双链表，设计并实现自己的链表。

单链表中的节点应该具备两个属性：val 和 next 。val 是当前节点的值，next 是指向下一个节点的指针/引用。

如果是双向链表，则还需要属性 prev 以指示链表中的上一个节点。假设链表中的所有节点下标从 0 开始。

实现 MyLinkedList 类：

MyLinkedList() 初始化 MyLinkedList 对象。
int get(int index) 获取链表中下标为 index 的节点的值。如果下标无效，则返回 -1 。
void addAtHead(int val) 将一个值为 val 的节点插入到链表中第一个元素之前。在插入完成后，新节点会成为链表的第一个节点。
void addAtTail(int val) 将一个值为 val 的节点追加到链表中作为链表的最后一个元素。
void addAtIndex(int index, int val) 将一个值为 val 的节点插入到链表中下标为 index 的节点之前。如果 index 等于链表的长度，那么该节点会被追加到链表的末尾。如果 index 比长度更大，该节点将 不会插入 到链表中。
void deleteAtIndex(int index) 如果下标有效，则删除链表中下标为 index 的节点。


示例：

输入
["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
[[], [1], [3], [1, 2], [1], [1], [1]]
输出
[null, null, null, null, 2, null, 3]

解释
MyLinkedList myLinkedList = new MyLinkedList();
myLinkedList.addAtHead(1);
myLinkedList.addAtTail(3);
myLinkedList.addAtIndex(1, 2);    // 链表变为 1->2->3
myLinkedList.get(1);              // 返回 2
myLinkedList.deleteAtIndex(1);    // 现在，链表变为 1->3
myLinkedList.get(1);              // 返回 3


提示：

0 <= index, val <= 1000
请不要使用内置的 LinkedList 库。
调用 get、addAtHead、addAtTail、addAtIndex 和 deleteAtIndex 的次数不超过 2000 。
*/


#include "iostream"
#include "vector"

using namespace std;


class MyLinkedList {
private:
    struct Node {
        int val;
        Node* next;
//        Node() : val(0), next(nullptr) {}
//        Node(int x) : val(x), next(nullptr) {}
        Node(int x, Node* p) : val(x), next(p) {}
    };

    Node* head;

public:
    MyLinkedList() {
        head = nullptr;
    }

    ~MyLinkedList() {
        Node* current = head;
        Node* next;
        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }
    }

    int get(int index) {
        Node* current = head;
        int now = 0;
        while (current != nullptr) {
            if (now == index) {
                return current->val;
            }
            current = current->next;
            now++;
        }
        return -1;
    }

    void addAtHead(int val) {
        Node* newHead = new Node(val, head);
        head = newHead;
    }

    void addAtTail(int val) {
        if (head == nullptr) {  // 如果链表为空，head 为空，addAtTail 会出错，因为在这种情况下你直接遍历链表，而 current 是 nullptr。
            head = new Node(val, nullptr);
            return;
        }
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        Node* newTail = new Node(val, nullptr);
        current->next = newTail;
    }

    void addAtIndex(int index, int val) {
        Node* current = head;
        int now = 1;
        if (index == 0) {
            Node* newHead = new Node(val, head);
            head = newHead;
            return;
        }
        while (current != nullptr) {
            if (index == now){
                Node* newNode = new Node(val, current->next);
                current->next = newNode;
            }
            current = current->next;
            now++;
        }
    }

    void deleteAtIndexGPT(int index) {
        if (index < 0 || head == nullptr) return;

        if (index == 0) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }

        Node* current = head;
        int now = 0;
        while (current->next != nullptr && now < index - 1) {
            current = current->next;
            now++;
        }

        if (current->next != nullptr) {
            Node* toDelete = current->next;
            current->next = current->next->next;
            delete toDelete;
        }
    }

    void deleteAtIndex(int index) {
        Node* current = head;
        int now = 1;
        if (index == 0) {
            Node* toDelete = head;
            head = current->next;
            delete toDelete;
            return;
        }
        while (current != nullptr) {
            if (index == now) {
                if (current->next != nullptr) {
                    current->next = current->next->next;
                }
            }
            current = current->next;
            now++;
        }
    }

    void travel() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->val << " --> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
};


int main() {
    MyLinkedList myLinkedList;

    myLinkedList.addAtHead(1);
    myLinkedList.travel();

    myLinkedList.addAtTail(3);
    myLinkedList.travel();

    myLinkedList.addAtIndex(1, 2);
    myLinkedList.travel();

    cout << myLinkedList.get(1) << endl;

    myLinkedList.deleteAtIndex(3);
    myLinkedList.travel();

    cout << myLinkedList.get(1) << endl;

    return 0;
}

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */