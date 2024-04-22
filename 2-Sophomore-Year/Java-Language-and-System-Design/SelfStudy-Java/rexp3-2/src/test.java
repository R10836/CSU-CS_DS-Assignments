import java.util.Scanner;

public class test {
    public static void main(String[] args){

        Graduate zhangsan = new Graduate("zhangsan", "男", 20);

        System.out.println("请输入每月工资：");
        Scanner sc1 = new Scanner(System.in);
        zhangsan.setPay(sc1.nextInt());

        System.out.println("请输入每学期学费：");
        Scanner sc2 = new Scanner(System.in);
        zhangsan.setFee(sc2.nextInt());

        int pays = zhangsan.getPay() * 12;
        int fees = zhangsan.getFee() * 2;
        int earn = pays - fees;
//        测试
        System.out.println(pays + "-" + fees + "=" + earn);

        if(earn <= 2000){
            System.out.println("You need a loan!");
        }else {
            System.out.println("You income is enough!");
        }

    }
}
