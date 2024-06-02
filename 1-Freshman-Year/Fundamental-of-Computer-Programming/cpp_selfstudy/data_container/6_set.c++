//
// Created by Shawn33712 on 24-6-1.
//
// c++ set数据容器操作。
// 按照构造、增、删、改、查、其他，说明。
// 并写一个全类型元素的遍历实现函数。

/*
    1. 元素的唯一性
set 容器中的每个元素都是唯一的。插入重复元素将不会改变集合的内容。例如，如果你尝试插入一个已经存在的元素，set 会忽略这个操作。
    2. 自动排序！
set 容器中的元素会自动按升序(小-->大)排序（默认情况下）。可以通过自定义比较器函数来改变排序顺序，但无论如何，set 都会保证元素的顺序。
    3. 高效的查找操作！
set 使用平衡二叉树（通常是红黑树）来存储元素，因此查找、插入和删除操作的时间复杂度为 O(log n)。这使得 set 在处理需要频繁查找的应用场景时非常高效。
    4. 迭代器
set 提供双向迭代器，可以使用这些迭代器来遍历集合中的元素。由于元素是有序的，迭代器按照排序顺序访问元素。
    5. 不允许修改元素值！
由于 set 使用键值来维护元素的唯一性和排序，不能直接修改集合中的元素。如果需要修改某个元素，通常的做法是先删除该元素，然后插入修改后的新值。
    6. 支持范围操作
set 提供一系列成员函数，如 lower_bound、upper_bound 和 equal_range，用于查找特定范围内的元素。这些函数利用 set 的有序特性，能高效地进行范围查询。
    7. 内部实现
set 容器通常基于红黑树实现。红黑树是一种自平衡二叉搜索树，确保插入、删除和查找操作的时间复杂度为 O(log n)。
*/

#include "iostream"
#include "set"
#include "vector"
using namespace std;


struct MyType1 {
    string name;
    double data;
    // 重载==运算符
    bool operator==(const MyType1& other) const {
        return name == other.name && data == other.data;
    }
    // 重载<运算符以便在set中排序！！！（set会自动排序）！！！
    bool operator<(const MyType1& other) const {
        // 首先比较 name 字段，如果相等再比较 data 字段
        if (name != other.name) {
            return name < other.name;
        }
        return data < other.data;
    }
    // 重载<<运算符
    friend ostream& operator<<(ostream& os, const MyType1& obj) {
        return os << "{" << obj.name << ", " << obj.data << "}";
    }
};


template <typename T> // 遍历集合
void traverseSet(const set<T>& s) {
    for (const auto& elem : s) {
        cout << elem << " ";
    }
    cout << endl;
}


int main() {
    // 创建
    set<int> set1; // 1. 创建空的set
    set<int> set2 = {1, 2, 3, 4, 5}; // 2. 使用初始值列表创建set
    vector<int> vec = {10, 20, 30, 40, 50};
    set<int> set3(vec.begin(), vec.end()); // 3. 使用范围（迭代器）创建set
    set<int> set4(set3); // 4. 使用拷贝构造函数创建set

    set<MyType1> sex1 = {{"Auto", 11.1}, {"Bear", 22.2}}; // 注意！set会自动排序，所以要重载比较运算符。

//    traverseSet(set1); //
//    traverseSet(set2); //1 2 3 4 5
//    traverseSet(set3); //10 20 30 40 50
//    traverseSet(set4); //10 20 30 40 50
//    traverseSet(sex1); //{Auto, 11.1} {Bear, 22.2}


    // 增
    set3.insert(-10086);
    set3.insert(30);
    sex1.insert({"Bear", 19.9});
    sex1.insert({"Bear", 22.2});

//    traverseSet(set3); //-10086 10 20 30 40 50
//    traverseSet(sex1); //{Auto, 11.1} {Bear, 19.9} {Bear, 22.2}


    // 删
    set3.erase(10086);
//    traverseSet(set3);
    set3.erase(-10086);
//    traverseSet(set3); //10 20 30 40 50


    // 改
    // set容器不支持直接修改元素，因为它保持元素的有序性和唯一性。要修改元素，需要先移除旧元素，再插入新元素：
    if (set3.find(10) != set3.end()) {
        set3.erase(10); // 移除旧元素 10
        set3.insert(25); // 插入新元素 25
    }
//    traverseSet(set3); //20 25 30 40 50


    // 查
    // 使用find方法查找元素，使用count方法检查元素是否存在:
    // find 方法用于在集合中查找特定元素。如果找到了该元素，返回一个指向该元素的迭代器；如果未找到该元素，则返回 end 迭代器。
    if (set3.find(30) != set3.end()) {
        cout << "exist" << endl;
    } else {
        cout << "extinct" << endl;
    }
    // count 方法用于统计集合中某个特定元素的个数。由于 set 容器中的元素都是唯一的，因此该方法的返回值要么是 0（元素不存在），要么是 1（元素存在）。
    if (set3.count(30)) {
        cout << "exist" << endl;
    } else {
        cout << "extinct" << endl;
    }


    // 其他
    // 获取元素个数
    size_t setSize = sex1.size(); // 获取集合的大小
//    cout << "Size of this set: " << setSize << endl; //Size of this set: 3

    // 清空集合
    set3.clear(); // 清空集合
    cout << "Is empty?: " << (set3.empty() ? "YES" : "NOP") << endl; //Is empty?: YES

    // 交换集合
    set4.swap(set2);
    traverseSet(set2); //10 20 30 40 50
    traverseSet(set4); //1 2 3 4 5


    return 0;
}
