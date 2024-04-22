public class Cylinder extends Circle{
    private double height;

    public Cylinder(double r, double h) {
        super.radius = r;
        this.height = h;
    }
    public double getHeight() {
        return height;
    }
    public  double getVol() {
        return Math.PI * radius * radius * height;
    }
    public double getArea() {
        return 2 * Math.PI * radius * height + 2 * Math.PI * radius * radius;
    }
    public void disp(){
        System.out.println("圆柱体的半径为：" + radius);
        System.out.println("圆柱体的高为：" + height);
        System.out.println("圆柱体的面积为：" + getArea());
        System.out.println("圆柱体的体积为：" + getVol());
    }
}
