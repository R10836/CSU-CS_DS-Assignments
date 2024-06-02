#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// 非修改序列操作
void non_modifying_operations() {
    vector<int> vec = {1, 2, 3, 4, 5};

    // std::for_each: 对范围内的每个元素执行给定的操作
    for_each(vec.begin(), vec.end(), [](int n) { cout << n << ' '; });
    cout << '\n';

    // std::find: 查找等于指定值的第一个元素
    auto it = find(vec.begin(), vec.end(), 3);
    if (it != vec.end()) {
        cout << "Found: " << *it << '\n';
    } else {
        cout << "Not found\n";
    }

    // std::find_if: 查找第一个满足条件的元素
    auto it2 = find_if(vec.begin(), vec.end(), [](int x) { return x > 3; });
    if (it2 != vec.end()) {
        cout << "Found: " << *it2 << '\n';
    } else {
        cout << "Not found\n";
    }

    // std::count: 统计范围内等于指定值的元素个数
    int cnt = count(vec.begin(), vec.end(), 3);
    cout << "Count of 3: " << cnt << '\n';

    // std::count_if: 统计范围内满足条件的元素个数
    int cnt2 = count_if(vec.begin(), vec.end(), [](int x) { return x > 3; });
    cout << "Count greater than 3: " << cnt2 << '\n';
}

// 修改序列操作
void modifying_operations() {
    vector<int> vec = {1, 2, 3, 4, 5};
    vector<int> result(vec.size());

    // std::transform: 将操作应用于输入范围的每个元素并将结果存储在另一个范围中
    transform(vec.begin(), vec.end(), result.begin(), [](int x) { return x + 1; });
    for (int n : result) { cout << n << ' '; }
    cout << '\n';

    // std::sort: 对范围内的元素进行排序
    sort(vec.begin(), vec.end());
    for (int n : vec) { cout << n << ' '; }
    cout << '\n';

    // std::reverse: 反转范围内的元素顺序
    reverse(vec.begin(), vec.end());
    for (int n : vec) { cout << n << ' '; }
    cout << '\n';

    // std::unique: 移除相邻的重复元素
    vec = {1, 2, 2, 3, 4, 4, 5};
    auto it = unique(vec.begin(), vec.end());
    vec.erase(it, vec.end());
    for (int n : vec) { cout << n << ' '; }
    cout << '\n';

    // std::remove: 移除等于指定值的元素，但不改变容器大小
    vec = {1, 2, 3, 4, 3, 5};
    auto it2 = remove(vec.begin(), vec.end(), 3);
    vec.erase(it2, vec.end());
    for (int n : vec) { cout << n << ' '; }
    cout << '\n';

    // std::remove_if: 移除满足条件的元素，但不改变容器大小
    vec = {1, 2, 3, 4, 5};
    auto it3 = remove_if(vec.begin(), vec.end(), [](int x) { return x > 3; });
    vec.erase(it3, vec.end());
    for (int n : vec) { cout << n << ' '; }
    cout << '\n';

    // std::copy: 将一个范围内的元素复制到另一个范围
    copy(vec.begin(), vec.end(), result.begin());
    for (int n : result) { cout << n << ' '; }
    cout << '\n';

    // std::copy_if: 只复制满足特定条件的元素
    vector<int> filtered;
    copy_if(vec.begin(), vec.end(), back_inserter(filtered), [](int x) { return x > 2; });
    for (int n : filtered) { cout << n << ' '; }
    cout << '\n';
}

// 排序和相关操作
void sorting_operations() {
    vector<int> vec = {5, 3, 1, 4, 2};

    // std::sort: 对范围内的元素进行排序
    sort(vec.begin(), vec.end());
    for (int n : vec) { cout << n << ' '; }
    cout << '\n';

    // std::partial_sort: 对部分元素排序
    vec = {5, 3, 1, 4, 2};
    partial_sort(vec.begin(), vec.begin() + 3, vec.end());
    for (int n : vec) { cout << n << ' '; }
    cout << '\n';

    // std::nth_element: 对第n个位置的元素进行排序
    vec = {5, 3, 1, 4, 2};
    nth_element(vec.begin(), vec.begin() + 2, vec.end());
    for (int n : vec) { cout << n << ' '; }
    cout << '\n';

    // std::stable_sort: 稳定排序，保持相等元素的顺序
    vec = {5, 3, 1, 4, 2};
    stable_sort(vec.begin(), vec.end());
    for (int n : vec) { cout << n << ' '; }
    cout << '\n';
}

// 数值操作
void numerical_operations() {
    vector<int> vec = {1, 2, 3, 4, 5};

    // std::accumulate: 计算范围内元素的累计和
    int sum = accumulate(vec.begin(), vec.end(), 0);
    cout << "Sum: " << sum << '\n';

    // std::inner_product: 计算两个范围内元素的内积
    vector<int> vec2 = {5, 4, 3, 2, 1};
    int product = inner_product(vec.begin(), vec.end(), vec2.begin(), 0);
    cout << "Inner product: " << product << '\n';

    // std::partial_sum: 计算部分和
    vector<int> result(vec.size());
    partial_sum(vec.begin(), vec.end(), result.begin());
    for (int n : result) { cout << n << ' '; }
    cout << '\n';

    // std::adjacent_difference: 计算相邻元素的差
    adjacent_difference(vec.begin(), vec.end(), result.begin());
    for (int n : result) { cout << n << ' '; }
    cout << '\n';
}

int main() {
    // 打印中文
    system("chcp 65001");
    cout << "----------" << endl;

    cout << "非修改序列操作:\n";
    non_modifying_operations();

    cout << "\n修改序列操作:\n";
    modifying_operations();

    cout << "\n排序和相关操作:\n";
    sorting_operations();

    cout << "\n数值操作:\n";
    numerical_operations();

    return 0;
}
