public class Sphere extends Circle {
    public Sphere() {
        super.radius = 0; // ?
    }
    public  Sphere(double r) {
        super.radius = r; // ?
    }
    public double getVol() {
        return (4.0 / 3.0) * Math.PI * radius * radius * radius;
    }
    @Override
    public  double getArea() {
        return 4 * Math.PI * radius * radius * radius;
    }
    public void disp() {
        System.out.println("球的半径为：" + radius);
        System.out.println("球的面积为：" + getArea());
        System.out.println("球的体积为：" + getVol());
    }
}
