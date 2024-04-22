public class Circle {
    protected double radius;
    public Circle(){
        radius = 0;
    }
    public Circle(double r) {
        radius = r;
    }
    double getRadius(){
        return radius;
    }
    public double getPerimeter() {
        return 2 * Math.PI * radius;
    }
    public double getArea(){
        return Math.PI * radius * radius;
    }
    public void disp(){
        System.out.println("圆的半径为：" + radius);
        System.out.println("圆的周长为：" + getPerimeter());
        System.out.println("圆的面积为：" + getArea());
    }
}
