//
// Created by 33712 on 24-5-29.
//
#include <iostream>
#include <string>

// 图形形状类 Shape
class Shape {
public:
    // 纯虚函数，计算图形的面积
    virtual double area() const = 0;

    // 纯虚函数，显示图形信息
    virtual void display() const = 0;
};

// 圆形类 Circle，继承自 Shape
class Circle : public Shape {
private:
    double m_radius; // 圆的半径

public:
    // 构造函数，传入圆的半径
    Circle(double radius) : m_radius(radius) {}

    // 计算圆的面积
    double area() const override {
        return 3.14159 * m_radius * m_radius; // 圆的面积公式
    }

    // 显示圆的信息
    void display() const override {
        std::cout << "Circle - Radius: " << m_radius << ", Area: " << area() << std::endl;
    }

    // 获取圆的半径
    double getRadius() const {
        return m_radius;
    }

    // 设置圆的半径
    void setRadius(double radius) {
        m_radius = radius;
    }
};

// 矩形类 Rectangle，继承自 Shape
class Rectangle : public Shape {
private:
    double m_width;  // 矩形的宽度
    double m_height; // 矩形的高度

public:
    // 构造函数，传入矩形的宽度和高度
    Rectangle(double width, double height) : m_width(width), m_height(height) {}

    // 计算矩形的面积
    double area() const override {
        return m_width * m_height; // 矩形的面积公式
    }

    // 显示矩形的信息
    void display() const override {
        std::cout << "Rectangle - Width: " << m_width << ", Height: " << m_height << ", Area: " << area() << std::endl;
    }

    // 获取矩形的宽度
    double getWidth() const {
        return m_width;
    }

    // 设置矩形的宽度
    void setWidth(double width) {
        m_width = width;
    }

    // 获取矩形的高度
    double getHeight() const {
        return m_height;
    }

    // 设置矩形的高度
    void setHeight(double height) {
        m_height = height;
    }
};

int main() {
    // 创建圆形和矩形对象
    Circle circle(5.0);
    Rectangle rectangle(4.0, 6.0);

    // 调用 display 方法显示图形信息
    circle.display();
    rectangle.display();

    // 修改圆形和矩形的属性，并再次显示
    circle.setRadius(7.0);
    rectangle.setWidth(5.0);
    rectangle.setHeight(7.0);

    circle.display();
    rectangle.display();

    return 0;
}
