//
// Created by 33712 on 24-5-30.
//

// 双向链表 list
// 链表中，不能像数组那样简单的将迭代器list.begin()+1，而是要prev(list.end())


#include "iostream"
#include "list"
#include "vector"
#include "string"
#include "algorithm"
using namespace std;


struct NewType {
    string name;
    double data;
    // 重载==运算符以便使用std::find查找
    bool operator==(const NewType& other) const {
        return name == other.name && data == other.data;
    }
    // 重载<<运算符以便输出
    friend ostream& operator<<(ostream& os, const NewType& obj) {
        return os << "{" << obj.name << ", " << obj.data << "}";
    }
};


template<typename T> // 遍历列表的模板函数
void traverseList(const list<T>& lst) {
    for (const auto& val : lst) {
        cout << val << " ";
    }
    cout << endl;
}

template<typename T> // 模板函数进行索引遍历
void traverseListByIndex(const list<T>& lst) {
    int index = 0;
    for (auto it = lst.begin(); it != lst.end(); ++it, ++index) {
//        cout << "Index " << index << ": " << *it << endl; // 换行
        cout << *it << " "; // 不换行
    }
    cout << endl;
}

template<typename T> // 查找元素的模板函数
bool findElement(const list<T>& lst, const T& value) {
    auto it = find(lst.begin(), lst.end(), value);
    return it != lst.end();
}

template<typename T> // 已知值，返回元素的索引
int findIndex(const list<T>& lst, const T& value) {
    auto it = find(lst.begin(), lst.end(), value);
    if (it != lst.end()) {
        return distance(lst.begin(), it);
    } else {
        return -1; // 如果没有找到元素，返回 -1
    }
}


int main() {
    // 初始化
    list<int> list1; // 创建一个空的list
    list<int> list2 = {1, 2, 3, 4, 5}; // 使用初始化列表初始化list
    list<int> list3(5, 100); // 创建一个包含5个元素的list，每个元素的值为100
    vector<int> vec = {1, 8, 8, 7, 4, 0, 5};
    list<int> list4(vec.begin(), vec.end()); // 使用vector的迭代器范围初始化list
    list<int> list5(list4); // 拷贝构造，使用list4初始化list5
//    traverseListByIndex(list1);
//    traverseListByIndex(list2);
//    traverseListByIndex(list3);
//    traverseListByIndex(list4);
//    traverseListByIndex(list5);

    list<NewType> lisp1;
    vector<NewType> vep = { {"Adam", 11.1}, {"Bobi", 22.2}, {"Cris", 33.3} };
    list<NewType> lisp2(vep.begin(), vep.end());
    list<NewType> lisp3(lisp2);
//    traverseListByIndex(lisp1);
//    traverseListByIndex(lisp2);
//    traverseListByIndex(lisp3);


    // 增
    list5.push_front(99); // 在列表的开头插入一个元素
    list5.push_back(-99); // 在列表的末尾插入一个元素

    list5.insert(next(list5.begin(), 5), 888);// 在指定位置插入元素
//    // 链式写法展开：
//    auto it = list5.begin();
//    auto nextIt = next(it, 5);
//    list5.insert(nextIt, 888);
    list5.insert(next(list5.begin(), 2), {100, 200});  // 在指定位置插入多个元素

//    traverseListByIndex(list5); //99 1 100 200 8 8 7 888 4 0 5 -99


    // 删
    lisp2.clear(); // 清空列表
//    traverseListByIndex(lisp2);

    list5.pop_front(); // 删除开头的元素
    list5.pop_back(); // 删除末尾的元素
    list5.erase(next(list5.begin(), 2));// 删除指定位置的元素

//    traverseListByIndex(list5); //1 100 8 8 7 888 4 0 5


    // 改
    *next(list2.begin(), 2) = -10086;
//    traverseListByIndex(list2); //1 2 -10086 4 5（是第3个而不是第2个）


    // 查
    // 直接定点访问迭代器的值
    cout << *next(list2.begin(), 0) << endl; //1

    // find查，返回的仍然是值。#include <algorithm>
    cout << *(find(list2.begin(), list2.end(), -10086)) << endl; //-10086
    cout << *(find(list2.begin(), prev(list2.end(), 4), -10086)) << endl; //2？？？难道是没找到的话，返回最后一个值？

    // RXY 自定义函数
    // 已知值知道元素的索引
    cout << "Index of " << -10086 << " in this list: " << findIndex(list2, -10086) << endl; //2
    cout << "Index of " << "{\"Adam\", 11.1}" << " in this list: " << findIndex(lisp3, {"Adam", 11.1}) << endl; //0


    // 其他
    // 获取大小
    cout << "List size: " << lisp3.size() << endl;

    // 检查是否为空
    if (lisp2.empty()) {
        cout << "List is empty" << endl;
    } else {
        cout << "List is not empty" << endl;
    }

    // 反转列表
    lisp3.reverse();
    for (NewType val : lisp3) {
        cout << val << " ";
    }
    cout << endl;

    // 排序列表（默认：小-->大）
    list2.sort();
    for (int val : list2) {
        cout << val << " ";
    }
    cout << endl;


    return 0;
}
