//
// Created by 33712 on 24-5-29.
//
#include "iostream"
#include "vector"
#include "sstream"
using namespace std;


struct NewTyp {
    char a;
    double b;
};
// 重载输出操作符用于自定义类型NewTyp
ostream& operator<<(ostream& os, const NewTyp& obj) {
    os << "{ classify: " << obj.a << ", value: " << obj.b << " }";
    return os;
}


template<typename T>
void traverseVector(const vector<T>& vec);  // 遍历（范围for循环）

template<typename T>
void traverseVectorWithIndex(const vector<T>& vec);  // 遍历（索引遍历）

template<typename T, size_t N>
vector<T> slice(const T (&arr)[N], int start, int end);  // 普通/动态数组切片（有重载）

vector<string > splitLineToWords(char splitKey);  // 分词，#include "sstream"


int main () {
    // 创建
    vector<int> original = {1, 2, 5, 8, 0};
    vector<int> v_1;
    vector<int> v_2 = {1, 2, 3, 4, 5};  // way2:创建一个带有5个整数的向量
    vector<int> v_3(8);  // way2:创建一个含有8个默认值的向量，默认值为0
    vector<int> v_4(8, -1);  // way3: 创建一个有8个值为-1的整数向量
    vector<int> v_5(original);  // way5: 创建一个original的副本
    vector<int> v_6(original.begin() + 1, original.end() - 1);  // way4: 从第2个到倒数第2个元素构造一个新的向量

    vector<NewTyp> vp_1;  // way1: 创建一个空的整数向量
    vector<NewTyp> vp_2 = {{'a', 1.11,}, {'b', 2.22}, {'c', 3.33}};

//    traverseVectorWithIndex(v_1);  //
//    traverseVectorWithIndex(v_2);  //1 2 3 4 5
//    traverseVectorWithIndex(v_3);  //0 0 0 0 0 0 0 0
//    traverseVector(v_4);  //-1 -1 -1 -1 -1 -1 -1 -1
//    traverseVector(v_5);  //1 2 5 8 0
//    traverseVector(v_6);  //2 5 8
//    traverseVectorWithIndex(vp_1);  //
//    traverseVectorWithIndex(vp_2);  //{ classify: a, value: 1.11 } { classify: b, value: 2.22 } { classify: c, value: 3.33 }
//    traverseVector(vp_2);  //{ classify: a, value: 1.11 } { classify: b, value: 2.22 } { classify: c, value: 3.33 }


    // 增
    int loc = 4;
    v_2.push_back(6);  // 在末尾添加元素6
//    traverseVectorWithIndex(v_2);  //1 2 3 4 5 6
    v_2.insert(v_2.begin() + loc, -77);  // 在第loc后，第loc+1前面插入值：{1, 2, 3, 4, 5, 6} --> {1, 2, 3, 4, -77, 5, 6}
//    traverseVectorWithIndex(v_2);  //1 2 3 4 -77 5 6
    v_2.insert(v_2.begin() + loc, 8, -77);  // 在。。。插入8个。。。
//    traverseVectorWithIndex(v_2);  //1 2 3 4 -77 -77 -77 -77 -77 -77 -77 -77 -77 5 6
    v_2.insert(v_2.begin() + loc, original.begin(), original.end());  // 在第loc后，第loc+1前面插入完整的original
//    traverseVectorWithIndex(v_2);  //1 2 3 4 1 2 5 8 0 -77 -77 -77 -77 -77 -77 -77 -77 -77 5 6

    vp_2.push_back({'d', 4.44});
//    traverseVectorWithIndex(vp_2);  //{ classify: a, value: 1.11 } { classify: b, value: 2.22 } { classify: c, value: 3.33 } { classify: d, value: 4.44 }


    // 删
    v_2.pop_back();  // 移除末尾元素6
//    traverseVectorWithIndex(v_2);  //1 2 3 4 1 2 5 8 0 -77 -77 -77 -77 -77 -77 -77 -77 -77 5
    v_2.erase(v_2.begin() + 4);  // 删除第(4+1)个位置的元素1
//    traverseVectorWithIndex(v_2);  //1 2 3 4 2 5 8 0 -77 -77 -77 -77 -77 -77 -77 -77 -77 5
    v_2.erase(v_2.begin() + 8, v_2.begin() + 18);  // 删除第(8+1)个位置的元素 至 第(18+1)个位置的元素（不包括）
//    traverseVectorWithIndex(v_2);  //1 2 3 4 2 5 8 0


    // 改
    v_4[0] = 10086;  // 将第1个位置的元素修改为10086，从0开始数数。
//    traverseVectorWithIndex(v_4);  //10086 -1 -1 -1 -1 -1 -1 -1
    v_4.at(2) = 12580;  // 将第3个位置的元素修改为12580，从0开始数数。
//    traverseVectorWithIndex(v_4);  //10086 -1 12580 -1 -1 -1 -1 -1
    v_4.assign(5, 250);  // 用5个值为250的元素替换掉原来的内容
//    traverseVectorWithIndex(v_4);  //250 250 250 250 250
    v_4.assign(original.begin() + 2, original.end()); // 使用original的一部分替换v中的元素，现在是{5, 8, 0};
//    traverseVectorWithIndex(v_4);  //5 8 0


    // 查
    int val1 = v_5[4];
    int val2 = v_5.at(0);
    int val3 = v_5.front();
    int val4 = v_5.back();
    cout << val1 << " " << val2 << " " << val3 << " " << val4 << endl;  //0 1 1 0

    NewTyp valp1 = vp_2[1];
    NewTyp valp2 = vp_2.at(2);
    NewTyp valp3 = vp_2.front();
    NewTyp valp4 = vp_2.back();
    cout << valp1.b << " " << valp2.a << " " << valp3.a << " " << valp4.b << endl;  //2.22 c a 4.44


    // 其他

    // 判断 `vector` 是否为空
    if (v_2.empty()) {  //Vector is not empty.
        cout << "Vector is empty." << endl;
    } else {
        cout << "Vector is not empty." << endl;
    }

    // 清空
    v_2.clear();
    if (v_2.empty()) {  //Vector is empty.
        cout << "Vector is empty." << endl;
    } else {
        cout << "Vector is not empty." << endl;
    }

    // 元素的数量
    cout << "Size of vector: " << vp_2.size() << endl;  //Size of vector: 4

    // 改变 `vector` 的大小，如果新的大小比当前大小大，则在末尾添加元素；如果小于当前大小，则移除多余的元素。
    vp_2.resize(2);
    cout << "Size of vector: " << vp_2.size() << endl;  //Size of vector: 2

    // 放弃多余的容量，将 `capacity` 缩小为 `size`。
    vp_2.shrink_to_fit();
    cout << "Size of vector: " << vp_2.size() << endl;


    // 自定义哦

    // 遍历（范围for循环）
    // 遍历（索引遍历）
    // 切片
    // 一行输入的分词

    return 0;
}


// RXY 遍历（范围for循环）
template<typename T>
void traverseVector(const vector<T>& vec) {
    // 使用范围for循环遍历vector
    for (const auto& elem : vec) {
        cout << elem << " ";  // 这里是打印
    }
    cout << endl;
}


// RXY 遍历（索引遍历）
template<typename T>
void traverseVectorWithIndex(const vector<T>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;
}


// RXY 普通/动态数组切片（有重载）
// 单纯传入数组名字（不加[]之类），区间为[start, end)。都返回一个切好片的 vector<T> 类型的对象。
template <typename T, size_t N>
vector<T> slice(const T (&arr)[N], int start, int end) {
    vector<T> result;
    for (int i = start; i < end && i < N; ++i) {
        result.push_back(arr[i]);
    }
    return result;
}
template <typename T>
vector<T> slice(const vector<T>& vec, int start, int end) {
    vector<T> result;
    for (int i = start; i < end && i < vec.size(); ++i) {
        result.push_back(vec[i]);
    }
    return result;
}


// RXY 读取一行输入，然后用空格分隔字符串，每个字符串存入一个动态数组并返回。要用#include "sstream"
// splitKey是分隔符，如splitLineToWords(' ')或splitLineToWords('@')等等。
vector<string > splitLineToWords(char splitKey) {
    vector<string> words;
    string line;

    // 读取一行输入
    getline(cin, line);  // 使用 getline(cin, line) 从标准输入流（通常是键盘输入）读取一行文本，并将其存储在 line 变量中。

    // 使用 stringstream 进行分割
    istringstream iss(line);  // 创建一个 istringstream 对象 iss，并将 line 字符串作为参数传递给它。这样做的目的是将 line 字符串转换为一个输入流，以便更容易地对其进行分割。
    string word;

    // 按 splitKey 分隔读取每个单词并存入数组
    while (getline(iss, word, splitKey)) {
        words.push_back(word);
    }

    return words;  // 将 words 动态数组作为结果返回。
}
