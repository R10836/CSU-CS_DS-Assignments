class Student:
    # __no = None
    # __name = None
    # __age = None

    # Python不支持方法的重载，在Python中，方法名是唯一标识符，不能有相同的方法名。定义多个同名方法，只有最后一个有效

    def __init__(self, no: str, name: str, age: int):
        self.__no = no
        self.__name = name
        self.__age = age

    # @property是一种装饰器，用于将一个方法转变为只读属性。相当于JAVA的getName。但使用 @property 装饰器可以使方法以属性的方式被访问，而不需要使用调用方法的括号。

    @property
    def no(self):
        return self.__no

    def name2(self):
        return self.__name

    @property
    def age(self):
        return self.__age

    # @变量名.setter是一个装饰器，用于定义一个 setter 方法，用于设置属性的值。相当于JAVA的setName。

    @no.setter
    def no(self, no):
        self.__no = no

    def name3(self, name):
        self.__name = name

    @age.setter
    def age(self, age):
        self.__age = age


stu1 = Student('8204', 'SHAWN', 21)
stu2 = Student('8208', 'DICK', 999)
print(stu1.no, stu1.name2(), stu1.age)
stu1.age = 4
print(stu1.no, stu1.name2(), stu1.age)
stu1.name3('RYAN')
print(stu1.no, stu1.name2(), stu1.age)

print((stu1.age + stu2.age) / 2)


# 测试函数，废话：
def test(a: int, b: float) -> (str, bool, float):
    if a - b >= 0:
        return '大', True, a - b
    else:
        return '小', False, a - b


if __name__ == '__main__':
    # print(test(5, 8.88))
    pass
