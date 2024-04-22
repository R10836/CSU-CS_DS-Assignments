public class test {
    public static void main(String[] args) {
        Rectangle rectangle = new Rectangle(3, 4);
        Circle circle = new Circle(3);
        System.out.println("矩形面积：" + rectangle.getArea());
        System.out.println("圆面积：" + circle.getArea());
    }
}