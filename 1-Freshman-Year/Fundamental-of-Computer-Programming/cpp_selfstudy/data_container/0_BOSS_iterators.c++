/*
 * 引入了 auto 关键字来自动推导变量的类型。使用 auto 声明迭代器有以下几个优点：

    简化代码：迭代器类型通常很长且复杂，使用 auto 可以使代码更简洁易读。
    减少错误：手动声明迭代器类型时容易出错，使用 auto 可以让编译器自动推导出正确的类型。
    增强可维护性：如果容器类型改变，使用 auto 的代码不需要修改，编译器会自动适应新的迭代器类型。
 *
 * */

/*
 * 《一个迭代器对应容器中的一个元素地址》，而不是一整个容器。

迭代器是一种用来遍历容器中元素的对象，它提供了一种访问容器元素的方法，允许程序员逐个访问容器中的元素。迭代器本质上是一个指针对象，它指向容器中的某个元素或者特定的位置。

每个迭代器通常指向容器中的一个元素，而不是整个容器。具体来说：

    对于顺序容器（如 vector、list、deque 等）：每个迭代器指向容器中的一个元素。

    对于关联容器（如 map、set、multimap、multiset 等）：迭代器指向的是容器中的键值对（pair），或者只是一个键（对于 set 和 multiset）。

    ！！！：迭代器本质上是指向容器中元素的《地址》，或者更精确地说，迭代器保存了对容器中元素的引用或指针。迭代器提供了一种访问容器元素的方法，允许程序员逐个访问容器中的元素。
 * */

#include <iostream>
#include <vector>
#include <list>
#include <iterator> // 包含advance、next、prev所需头文件
#include <algorithm> // 有了algorithm，iterator就变黑了。。。

using namespace std;


int main() {
    // 初始化容器
    vector<int> vec = {1, 2, 3, 4, 5};
    list<int> lst = {6, 7, 8, 9, 10};

    // 0. 先明确begin()和end()是哪个迭代器！且返回的是迭代器，故要*取值！
    auto beginFuck = vec.begin(); // 返回一个指向容器第一个元素的迭代器
    auto endFuck = vec.end();     // 返回一个指向容器《最后一个元素的后一个位置》的迭代器
    auto endFuckPre1 = prev(vec.end());   // end() 返回的是指向容器最后一个元素后面的位置的迭代器，而不是最后一个元素本身。因此，如果你想访问容器中的最后一个元素，可以使用 end() 结合 prev() 函数来获取最后一个元素的迭代器，然后通过该迭代器来访问该元素。
    cout << *beginFuck << " " << *endFuck << " " << *endFuckPre1 << endl;

    // 1. 使用begin()和end()遍历vector
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 2. 使用rbegin()和rend()反向遍历list
    for (auto it = lst.rbegin(); it != lst.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 3. 使用advance()前进迭代器
    auto lstIt = lst.begin();
    advance(lstIt, 3); // 前进3个位置
    cout << "Element after advancing 3 positions: " << *lstIt << endl; // 输出：9

    // 4. 使用next()获取前进后的迭代器（-->）。默认值为1。
    auto nextIt = next(lst.begin(), 2);
    cout << "Element at next position: " << *nextIt << endl; // 输出：8

    // 5. 使用prev()获取后退后的迭代器（<--）。默认值为1。
    auto prevIt = prev(lst.end(), 2);
    cout << "Element at prev position: " << *prevIt << endl; // 输出：9

    // 6. 在指定位置插入元素
    vec.insert(next(vec.begin(), 2), 99); // 在vec第3个位置插入元素99。注意！这是将原第3个元素顶到第4个了，以此类推。
    for (auto val : vec) {
        cout << val << " ";
    }
    cout << endl; // 输出：1 2 99 3 4 5

    // 7. 删除指定位置的元素
    vec.erase(next(vec.begin(), 2));
    for (auto val : vec) {
        cout << val << " ";
    }
    cout << endl; // 输出：1 2 3 4 5

    // 8. 使用emplace()和emplace_back()构造并插入元素。（要插入元素的位置, 要传递给元素构造函数的参数）
    vec.emplace(vec.begin() + 1, 100);
    vec.emplace_back(200);
    for (auto val : vec) {
        cout << val << " ";
    }
    cout << endl; // 输出：1 100 2 3 4 5 200

    // 9. 使用push_back()和push_front()插入元素
    lst.push_front(5); // 前插
    lst.push_back(11); // 后插
    for (auto val : lst) {
        cout << val << " ";
    }
    cout << endl; // 输出：5 6 7 8 9 10 11

    // 10. 使用pop_back()和pop_front()删除元素
    lst.pop_front(); // 前出
    lst.pop_back(); // 后出
    for (auto val : lst) {
        cout << val << " ";
    }
    cout << endl; // 输出：6 7 8 9 10

    // 11. 使用clear()清空容器
//    vec.clear();
//    cout << "Size after clear: " << vec.size() << endl; // 输出：0


    cout << "--------------PLUS--------------" << endl;
    //vec: 1 100 2 3 4 5 200
    //lst: 6 7 8 9 10

    // 12. size()获取容器中元素的个数
    cout << "Size of vector: " << vec.size() << endl;  //7
    cout << "Size of list: " << lst.size() << endl;  //5

    // 13. front()和back()获取容器中第一个元素和最后一个元素！返回的直接是元素，不用*取值！
    cout << "First element: " << vec.front() << endl; // 输出：1
    cout << "Last element: " << lst.back() << endl;   // 输出：10

    // 14. resize()改变容器中元素的个数
    lst.resize(10); // 将容器的大小调整为5，新增的元素用默认值填充
    for (int val : lst) {
        cout << val << " ";
    }
    cout << endl; // 输出：6 7 8 9 10 0 0 0 0 0

    // 15. swap()交换两个容器的内容
    vector<int> vec1 = {1, 2, 3};
    vector<int> vec2 = {4, 5, 6};
    vec1.swap(vec2);
    cout << "vec1: ";
    for (int val : vec1) {
        cout << val << " ";
    }
    cout << endl; // 输出：4 5 6
    cout << "vec2: ";
    for (int val : vec2) {
        cout << val << " ";
    }
    cout << endl; // 输出：1 2 3

    // 16. assign()用新元素替换容器中的内容，元素数目可以不同。
    vec.assign({11, 22, 33, 44});
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl; // 输出：11, 22, 33, 44

    // 17. reverse()反转容器中元素的顺序，要用#include <algorithm>
    reverse(vec.begin(), vec.end());
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl; // 输出：44 33 22 11

    // 18. sort()对容器中的元素进行排序（小-->大），要用#include <algorithm>
    sort(vec.begin(), vec.end());
//    sort(lst.begin(), lst.end()); //list类型不能排。。。
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl; // 输出：11 22 33 44

    // 19. find()在容器中查找指定元素的位置（从0计数），要用#include <algorithm>
    auto sh_it = find(vec.begin(), vec.end(), 33); // 查找元素33的位置
    if (sh_it != vec.end()) {
        cout << "Element found at position: " << distance(vec.begin(), sh_it) << endl; // 输出：Element found at position: 2
    } else {
        cout << "Element not found." << endl;
    }


    return 0;
}
