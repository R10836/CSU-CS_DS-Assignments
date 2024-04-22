import math


class Circle:

    def __init__(self, radius):
        self._radius = radius

    @property
    def radius(self) -> float:
        return self._radius

    @radius.setter
    def radius(self, value):
        self._radius = value

    def perimeter(self) -> float:
        return 2 * math.pi * self._radius

    def area(self) -> float:
        return math.pi * pow(self._radius, 2)

    def disp(self):
        print('圆的半径为：%f。圆的周长为：%f。圆的面积为：%f。' % (self.radius, self.perimeter(), self.area()))


class Sphere(Circle):
    def __init__(self, radius):
        super().__init__(radius)

    def vol(self):
        return 4 / 3 * math.pi * self.radius ** 3

    # 在 Python 中，方法的重写是通过在子类中重新定义与父类相同名称的方法来实现的。当子类中重新定义了父类的方法时，子类的实例在调用该方法时将使用子类中的定义，而不是父类中的。
    def area(self):
        return 4 * math.pi * self.radius ** 2

    def disp(self):
        print(f"球的半径为：{self.radius}，球的表面积为：{self.area()}，球的体积为：{self.vol()}")


class Cylinder(Circle):
    def __init__(self, radius, height):
        super().__init__(radius)
        self._height = height

    @property
    def height(self):
        return self._height

    @height.setter
    def height(self, value):
        self._height = value

    def vol(self):
        return math.pi * self._radius ** 2 * self._height

    def area(self):
        return 2 * math.pi * self._radius * (self._radius + self._height)

    def disp(self):
        print(
            f"圆柱体的半径为：{self.radius}，高为：{self.height}，表面积为：{self.area()}，体积为：{self.vol()}")


cir = Circle(10)
cir.disp()
sph = Sphere(10)
sph.disp()
cyl = Cylinder(10, 5)
cyl.disp()