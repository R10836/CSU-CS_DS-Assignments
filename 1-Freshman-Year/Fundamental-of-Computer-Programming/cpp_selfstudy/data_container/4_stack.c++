//
// Created by Shawn33712 on 24-5-31.
//
// c++ stack数据容器
#include "iostream"
#include "stack"
#include "vector"
using namespace std;


struct NewTy {
    string name;
    double data;
    // 重载==运算符
    bool operator==(const NewTy& other) const {
        return name == other.name && data == other.data;
    }
    // 重载<<运算符
    friend ostream& operator<<(ostream& os, const NewTy& obj) {
        return os << "{" << obj.name << ", " << obj.data << "}";
    }
};


template <typename T> // 破坏栈结构的遍历（顶-->底）
void roughTrvStk(stack<T> myStack) {
    while (!myStack.empty()) {
        cout << myStack.top() << " "; // 输出当前栈顶元素
        myStack.pop(); // 移除当前栈顶元素
    }
    cout << endl;
}

template <typename T> // 不破坏的遍历（顶-->底）
void smoothTrvStk(stack<T>& myStack) {
    stack<T> tempStack; // 创建一个临时栈来保存元素
    // 遍历栈并输出元素，同时将元素移到临时栈
    while (!myStack.empty()) {
        T topElement = myStack.top();
        cout << topElement << " "; // 输出当前栈顶元素
        tempStack.push(topElement); // 将元素压入临时栈
        myStack.pop(); // 移除原栈顶元素
    }
    cout << endl;
    // 将元素从临时栈移回原栈，恢复原栈结构
    while (!tempStack.empty()) {
        myStack.push(tempStack.top());
        tempStack.pop();
    }
}


int main() {
    stack<int> originalStack;
    originalStack.push(1);
    originalStack.push(2);
    originalStack.push(3);

    // 构造
    // 在C++标准库中，stack类并不直接支持带容器的构造函数，而是通过默认构造函数或拷贝构造函数进行初始化。对于拷贝构造，标准的stack类已经提供了默认实现。
    stack<int> stk1; // 1. 默认构造函数
    stack<int> stk2(originalStack); // 2. 拷贝构造函数

    stack<NewTy> stc1;


    // 增
    stk1.push(10); // 将 10 压入栈
    stk1.push(20); // 将 20 压入栈
    stk1.push(30); // 将 30 压入栈
//    smoothTrvStk(stk1); //30 20 10

    stc1.push({"Ace", 11.1});
    stc1.push({"Bob", 22.2});
    stc1.push({"Cop", 33.3});
//    smoothTrvStk(stc1); //{Cop, 33.3} {Bob, 22.2} {Ace, 11.1}


    // 删
    stk2.pop(); // 移除栈顶元素，并不返回被移除的元素
//    smoothTrvStk(stk2); //2 1


    // 改
    // stack 只能从栈顶添加或移除元素，因此没有直接的方法来修改栈中的其他元素，但可以通过pop和push操作间接修改栈顶元素
    if (!stc1.empty()) {
    NewTy topElement = stc1.top(); // 获取栈顶元素
    stc1.pop(); // 移除栈顶元素
    topElement = {topElement.name + " fucker", topElement.data + 0.007}; // 修改栈顶元素
    stc1.push(topElement); // 将修改后的元素重新压入栈顶
    }
//    smoothTrvStk(stc1); //{Cop fucker, 33.307} {Bob, 22.2} {Ace, 11.1}


    // 查
    // 使用top方法访问栈顶元素
    if (!stc1.empty()) {
        cout << "栈顶元素: " << stc1.top() << endl; // 输出当前栈顶元素：鏍堥《鍏冪礌: {Cop fucker, 33.307}
    } else {
        cout << "栈是空的" << endl;
    }


    // 其他
    // 判空
    bool isEmpty = stk1.empty(); // 如果栈为空，返回 true，否则返回 false
//    cout << "Is stack empty?: " << (isEmpty ? "Yes" : "No") << endl;

    // 元素个数
    size_t stackSize = stk2.size(); // 获取栈的大小
//    cout << "Stack's size: " << stackSize << endl; //Stack's size: 2

    // 交换栈
    stk1.swap(stk2);
//    smoothTrvStk(stk1); //2 1
//    smoothTrvStk(stk2); //30 20 10


    return 0;
}