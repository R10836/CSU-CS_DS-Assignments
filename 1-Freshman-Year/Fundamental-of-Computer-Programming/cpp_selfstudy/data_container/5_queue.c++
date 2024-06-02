//
// Created by Shawn33712 on 24-6-1.
//
//c++ queue数据容器操作。
//按照构造、增、删、改、查、其他，说明。
//并写一个全类型元素的遍历实现函数。
#include "iostream"
#include "queue"
using namespace std;


struct MyType {
    string name;
    double data;
    // 重载==运算符
    bool operator==(const MyType& other) const {
        return name == other.name && data == other.data;
    }
    // 重载<<运算符
    friend ostream& operator<<(ostream& os, const MyType& obj) {
        return os << "{" << obj.name << ", " << obj.data << "}";
    }
};


template <typename T> // 遍历队列
void printQueue(queue<T> q) {
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}


int main() {
    // 构造
    queue<int> queue1;

    queue<MyType> queen1;


    // 增
    queue1.push(10); // 将 10 添加到队列
    queue1.push(20); // 将 20 添加到队列
    queue1.push(30); // 将 30 添加到队列
//    printQueue(queue1); //10 20 30

    queen1.push({"Alice", 1.1}); // 将 10 添加到队列
    queen1.push({"Bloom", 2.2}); // 将 20 添加到队列
    queen1.push({"Chris", 3.3}); // 将 30 添加到队列
    queen1.push({"Daisy", 4.4}); // 将 30 添加到队列
//    printQueue(queen1); //{Alice, 1.1} {Bloom, 2.2} {Chris, 3.3} {Daisy, 4.4}


    // 删
    queen1.pop();
//    printQueue(queen1); //{Bloom, 2.2} {Chris, 3.3} {Daisy, 4.4}


    // 改
    // queue 容器不能直接修改任意元素，只能通过先移除再添加的方式间接修改队列头部元素
    if (!queue1.empty()) {
        int frontElement = queue1.front(); // 获取队列头部元素
        queue1.pop(); // 移除队列头部元素
        frontElement += 80000; // 修改元素
        queue1.push(frontElement); // 将修改后的元素添加回队列末尾
    }
//    printQueue(queue1); //20 30 80010


    // 查
    // 使用front方法和back方法访问队列头部和尾部的元素：
    if (!queen1.empty()) {
        cout << "queue's head: " << queen1.front().name + " " << queen1.back().data << endl; // 输出队列头部元素：queue's head: Bloom 4.4
        cout << "queue's tail: " << queen1.back().name + " " << queen1.back().data << endl; // 输出队列尾部元素：queue's tail: Daisy 4.4
    }


    // 其他
    // 判空
    bool isEmpty = queen1.empty(); // 如果队列为空，返回 true，否则返回 false
//    cout << "Is it empty?: " << (isEmpty ? "Y" : "N") << endl; //Is it empty?: N

    // 获取元素个数
    size_t queueSize = queen1.size(); // 获取队列的大小
//    cout << "The queue's size: " << queueSize << endl; //The queue's size: 3

    // 交换
    queue<MyType> queen2;
    queen1.swap(queen2);
    printQueue(queen1); //
    printQueue(queen2); //{Bloom, 2.2} {Chris, 3.3} {Daisy, 4.4}


    return 0;
}
