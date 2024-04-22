import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String obj = sc.next();
        double r = sc.nextDouble();

        if(obj.equals("circle")) {
            Circle c = new Circle(r);
            c.disp();
        } else if (obj.equals("sphere")) {
            Sphere c = new Sphere(r);
            c.disp();
        } else if (obj.equals("cylinder")) {
            System.out.println("再输入一个值作为高：");
            double h = sc.nextDouble();
            Cylinder c = new Cylinder(r, h);
            c.disp();
        }else {
            System.out.println("请输入circle、sphere、cylinder中的一个！");
        }
    }
}
