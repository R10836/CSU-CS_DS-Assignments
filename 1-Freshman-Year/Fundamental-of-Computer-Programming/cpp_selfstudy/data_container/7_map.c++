#include <iostream>
#include <map>
#include <string>

using namespace std;

template <typename K, typename V>
void printMap(const map<K, V>& m) {
    for (const auto& pair : m) {
        cout << pair.first << " => " << pair.second << endl;
    }
}

int main() {
    // 打印中文
    system("chcp 65001");
    cout << "----------" << endl;

    // 构造
    map<string, int> myMap;

    // 增
    myMap.insert({"Alice", 30}); // 1. 使用 insert 添加元素
    myMap["Bob"] = 40; // 2. 使用 operator[] 添加元素
    myMap["Charlie"] = 50;
    myMap["Dean"] = -10086;
    printMap(myMap);
    cout << "----------" << endl;

    // 删
    myMap.erase("Dean"); // 移除键为 "Dean" 的元素
    printMap(myMap);
    cout << "----------" << endl;

    // 改
    myMap["Alice"] = 1887405; // 修改键为 "Alice" 的元素的值
    printMap(myMap);
    cout << "----------" << endl;

    // 查
    // 使用find方法查找元素，使用operator[]或at方法访问元素的值：

    // 使用 find 方法查找元素
    auto it = myMap.find("Charlie");
    if (it != myMap.end()) {
        cout << "找到元素: " << it->first << " => " << it->second << endl;
    } else {
        cout << "未找到元素 'Charlie'" << endl;
    }
    // 使用 operator[] 访问元素的值
    cout << "Alice 的值是: " << myMap["Alice"] << endl;
    // 使用 at 方法访问元素的值
    try {
        cout << "Charlie 的值是: " << myMap.at("Charlie") << endl;
    } catch (const out_of_range& e) {
        cout << "未找到键 'Charlie'" << endl;
    }
    cout << "----------" << endl;

    // 其他

    // 获取映射中的元素个数
    cout << "映射的大小: " << myMap.size() << endl;

    // 交换映射
    map<string, int> anotherMap = {{"Dave", 60}, {"Eve", 70}};
    myMap.swap(anotherMap);
    cout << "myMap: " << endl;
    printMap(myMap); // 打印 myMap 中的所有元素
    cout << "anotherMap: " << endl;
    printMap(anotherMap); // 打印 anotherMap 中的所有元素

    // 清空映射
//    myMap.clear(); // 清空映射

    return 0;
}
