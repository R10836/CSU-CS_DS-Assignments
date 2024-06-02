//
// Created by 33712 on 24-5-29.
//
#include "iostream"
#include "string"
#include "algorithm"
#include "limits"
using namespace std;


int main() {
    // 初始化
    string str1; // 空字符串
    string str2 = "hi hi hi"; // 空字符串
    string str3("Hello, World!"); // 用C风格字符串初始化
    string str4(str2); // 拷贝构造
    string str5(5, 'A'); // 初始化为5个'A'
//    cout << str1 << endl;  //
//    cout << str2 << endl;  //hi hi hi
//    cout << str3 << endl;  //Hello, World!
//    cout << str4 << endl;  //hi hi hi
//    cout << str5 << endl;  //AAAAA


    // 增、改
    string str6 = str4 + str5;  // 连接
//    cout << str6 << endl;

    str5.insert(1, 5, 'Z');  // 插入字符 （插入位置的索引(从0开始)， 要插入的字符数量， 要插入的字符） "AZZZZZAAAA"
    str5.insert(0, "Python");  // 插入一个字符串 （插入位置的索引， 要插入的字符串）： "PythonAZZZZZAAAA"
    str5.insert(1, "jeopardize", 0, 3);  // 插入一个字符串的一部分 （插入位置的索引， 要插入的字符串， 子字符串的起始位， 选取子字符串的长度）： "PjeoythonAZZZZZAAAA"
//    cout << str5 << endl;

    str2.replace(1, 3, "JavaJavaJavaJava");  // 替换 （从字符串的哪个位置开始替换， 从字符串的哪个位置开始替换， 要插入的新字符串）: "hJavaJavaJavaJavai hi"
    str2.replace(2, 10, "CppCppCpp", 1, 3);  // 替换 （从字符串的哪个位置开始替换， 从字符串的哪个位置开始替换， 要插入的新字符串, 新字符串的起始位， 选取新字符串长度）: "hJppCaJavai hi"
//    cout << str2 << endl;


    // 删
    str3.erase(1, 5);  // "Hello, World!" --> "H World!"
    cout << str3 << endl;

    str6.clear();  // 清空字符串。
//    cout << str6 << endl;  //


    // 查 （size_t是无符号整数类型。）

    size_t pos5 = str3.find(" Wor");  // 查找子字符串在字符串中首次出现的位置
    size_t pos6 = str3.find(" wor");  // 如果未找到，则返回std::string::npos。
    size_t pos7 = str3.find("Wo", 5);  // 可以指定从哪个位置开始查找,比如这样就找不到“Wo”了
//    cout << pos5 << ' ' << pos6 << " " << pos7 << endl;

    size_t pos8 = str3.rfind("Wo"); // 从字符串末尾向前查找子字符串的首次出现位置。
//    cout << pos8 << endl;  // ！！！只是反着查，返回值仍是正序的，这里是2

    size_t pos1 = str3.find_first_of("abclmno");  //查找第一个不属于指定字符集的字符。
//    cout << pos1 << endl;  // 这里返回3即'o'的位置，虽然查找中l先被查到，但l位置在o之后

    size_t pos2 = str3.find_last_of("abclmno");// 查找字符串中最后一次出现指定字符集中的任意字符的位置。
//    cout << pos2 << endl;  // 这里返回5即'l'的位置

    size_t pos3= str3.find_first_not_of("H,Worl");// 查找最后一个不属于指定字符集的字符。
//    cout << pos3 << endl;  //这里返回1即' '的位置，而不是d的位置

    size_t pos4= str3.find_last_not_of("H,Worl");//查找最后一个不属于指定字符集的字符。
//    cout << pos4 << endl;  //这里返回7即d的位置，而不是' '的位置


    // 其他
    string input1, input2;

    //！！！在使用 getline 读取一行文本之前，如果前面有其他 cin 操作（例如读取整数），需要清除输入缓冲区中的换行符。
    int a;
    cin >> a;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  //#include "limits"。cin.ignore()只忽略输入缓冲区中的下一个字符。而这个忽略输入缓冲区中直到遇到换行符为止的所有字符。
    getline(cin, input1);  // 从标准输入（或其他输入流）读取一行字符，直到遇到换行符（或指定的分隔符）。
    getline(cin, input2, ';'); // 从标准输入读取，直到遇到分号

    cout << str2.length() << " " << str2.size() << endl;  // 获取字符串的长度或大小，length() 和 size() 方法是等价的。
    //14 14

    // 切片
    string str = "Hello, World!";
    string subStr = str.substr(7, 5); // 使用 substr 函数可以提取字符串的子字符串。这里从位置7开始，提取5个字符。
    cout << subStr << endl; // 输出 "World"

    // 字符串比较
    string str7 = "i love";
    string str8 = "i love u";
    cout << (str7 == str8) << ' ' << (str7 < str8) << endl;  //0 1
    // 字符串可以使用标准的比较操作符进行比较，比如 ==, !=, <, >, <=, >= 等。

    // 反转字符串,要用#include "algorithm"
    reverse(str8.begin(), str8.end());  //u evol i
    cout << str8 << endl;

    // 转大写
    transform(str7.begin(), str7.end(), str7.begin(), ::toupper);  //I LOVE
    cout << str7 << endl;

    // 转小写
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);  //hjppcajavai hi
    cout << str2 << endl;

    // 判空
    cout << str2.empty() << " " << str1.empty() << endl;  //0 1(空为1，有为0)


    return 0;
}
