//
// Created by 33712 on 24-5-29.
//
#include <iostream>
#include <string>

// 用户类
class User {
private:
    std::string m_name; // 用户姓名
    int m_age;          // 用户年龄

public:
    // 构造函数
    User(const std::string& name, int age) : m_name(name), m_age(age) {}

    // 设置姓名
    void setName(const std::string& name) {
        m_name = name;
    }

    // 获取姓名
    std::string getName() const {
        return m_name;
    }

    // 设置年龄
    void setAge(int age) {
        m_age = age;
    }

    // 获取年龄
    int getAge() const {
        return m_age;
    }

    // 显示用户信息
    void displayInfo() const {
        std::cout << "Name: " << m_name << ", Age: " << m_age << std::endl;
    }
};

int main() {
    // 创建用户对象
    User user("Alice", 30);

    // 获取和修改用户信息
    std::cout << "Original Name: " << user.getName() << std::endl;
    user.setName("Bob");
    std::cout << "New Name: " << user.getName() << std::endl;

    user.displayInfo();

    return 0;
}
