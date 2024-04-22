import java.util.Scanner;

public class test {
        public static void main(String[] args) throws IllegalAgeException {
            Scanner sc = new Scanner(System.in);

            Person p = new Person();

            while (true) {
                try {
                    System.out.println("请输入p的年龄：");
                    String age = sc.nextLine();
                    p.setAge(Integer.parseInt(age));
                    break;
                } catch (NumberFormatException e) {
                    e.printStackTrace();
                } catch (IllegalAgeException e) {
                    e.printStackTrace();
                }
            }
            System.out.println("你设置p的年龄为：" + p.getAge());
        }
}
