import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        // 创建一个 Graduate 对象 stu1
        Graduate stu1 = new Graduate("zhangsan", "男", 23);

        // 创建一个 Scanner 对象用于读取输入
        Scanner input1 = null;
        try {
            input1 = new Scanner(System.in);
            System.out.println("请输入" + stu1.name + "的每月工资(12)和每学期学费(2)：");
            // 读取输入的工资和学费
            int pay = input1.nextInt(); //工资
            int fee = input1.nextInt(); //学费

            // 设置 Graduate 对象的工资和学费
            stu1.setpay(pay);
            stu1.setfee(fee);

            // 计算：工资-学费
            int subs = stu1.income() - stu1.tuition();
            System.out.println(stu1.income() + "-" + stu1.tuition() + "=" + subs);

            // 判断是否需要贷款
            if (subs <= 2000) {
                System.out.println("You need a loan!");
            } else {
                System.out.println("You income is enough!");
            }
        } finally {
            // 关闭 Scanner 对象，释放资源
            if (input1 != null) {
                input1.close();
            }
        }
    }
}
