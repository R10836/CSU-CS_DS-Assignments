import java.io.*;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) throws Exception{

        t1();
        t2();
        t2_2();
        t3();
        t4();
        t5();
        t6();
        t7();
        t8t9();

    }

    //将其中的大写英文字母改为小写字母，小写字母改为大写字母，然后输出。
    public static void t1() {

        System.out.println("----------------1----------------");
        System.out.println("请输入一个字符串：");
        Scanner sc = new Scanner(System.in);
        String str = sc.next();

        String result = "";
        for (int i = 0; i < str.length(); i++) {
            char ch = str.charAt(i);
            if (ch <= 'Z' && ch >= 'A') {
                ch += 32;
            } else if (ch <= 'z' && ch >= 'a') {
                ch -= 32;
            }
            result = result + ch;
        }
        System.out.println("结果是" + result);
    }

    //检查输入的字符串是否是“回文”，
    public static void t2() {

        System.out.println("----------------2----------------");
        System.out.println("请输入一个字符串：");
        Scanner sc = new Scanner(System.in);
        String str = sc.next();

        int flag = 0;
        for (int i = 0; i < (str.length())/2; i++) {
            if (str.charAt(i) != str.charAt(str.length() - 1 - i)) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            System.out.println(str + "是回文");
        } else {
            System.out.println(str + "不是回文");
        }
    }

    //第二题再用 StringBuilder 和 链式编程 再写一遍！
    public static void t2_2(){

        System.out.println("----------------2----------------");
        System.out.println("请输入一个字符串：");
        Scanner sc = new Scanner(System.in);
        String str = sc.next();

//        StringBuilder sb = new StringBuilder();
//        sb.append(str);
//        sb.reverse();
//        String result = sb.toString();

        String result = new StringBuilder(str).reverse().toString();

        if (str.equals(result)) {
            System.out.println(str + "是回文");
        } else {
            System.out.println(str + "不是回文");
        }
    }

    //输入两个字符串，从第一个字符串中删除第二个字符串的内容。
    public static void t3() {

        System.out.println("----------------3----------------");
        System.out.println("请输入第一个字符串：");
        Scanner sc1 = new Scanner(System.in);
        String str1 = sc1.next();
        System.out.println("请输入第二个字符串：");
        Scanner sc2 = new Scanner(System.in);
        String str2 = sc2.next();

        String result = "";
        for (int i = 0; i < str1.length(); i++) {
            for (int j = 0; j < str2.length(); j++) {
                if (str1.charAt(i) == str2.charAt(j)) {
                    break;
                } else if (j == str2.length() - 1){
                    result = result + str1.charAt(i);
                }
            }
        }
        System.out.println("结果是" + result);
    }

    //4.从命令行方式输入的字符串中删去所有重复的字符，每种字符只保留一个。
    public static void t4() {

        System.out.println("----------------4----------------");
        System.out.println("请输入一个字符串：");
        Scanner sc = new Scanner(System.in);
        String str = sc.next();

        String result = "";
        result = result + str.charAt(0);
        for (int i = 1; i < str.length(); i++) {
            for (int j = 0; j < result.length(); j++) {
                if (str.charAt(i) == result.charAt(j)) {
                    break;
                } else if (j == result.length() - 1) {
                    result = result + str.charAt(i);
                }
            }
        }
        System.out.println("结果是" + result);
    }

    //统计一个字符串中给定字符串出现的频率。
    public static void t5() {
        System.out.println("----------------5----------------");
        System.out.println("请输入一个字符串：");
        Scanner sc = new Scanner(System.in);
        String str = sc.next();
        System.out.println("请输入给定字符串：");
        Scanner sc2 = new Scanner(System.in);
        String str2 =sc2.next();

        int count = 0;
        int j = 0;
        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) == str2.charAt(j)) {
                j++;
                if (j == str2.length()) {
                    count++;
                    j = 0;
                }
            } else {
                j = 0;
            }
        }
        System.out.println("该字符出现的频率为：" + count);
    }

    //将一个表示十进制数的字符串转换为以逗号分隔的字符串，从右边开始每三个数字标一个逗号。
    public static void t6(){

        System.out.println("----------------6----------------");
        System.out.println("请输入一个字符串：");
        Scanner sc = new Scanner(System.in);
        String str = sc.next();

        String result = "";
        int add = (str.length() -1) / 3;
        int head = str.length() % 3;
        if (head == 0){
            head = 3;
        }

        if (add != 0) {
            for (int j = 0; j < head; j++) {
                result = result + str.charAt(j);
            }
            result = result + ",";

            for (int j = 0; j < add; j++) {
                for (int k = 0; k < 3; k++) {
                    result = result + str.charAt(head + k + 3 * j);
                }
                if (j != add - 1) {
                    result = result + ",";
                }
            }
        } else {
            result = str;
        }

        System.out.println("结果是" + result);
    }

    //7.求2~200之间的所有素数，将求得的结果保存到PRIME.DAT文件中。
    public static void t7() throws IOException {
        System.out.println("----------------7----------------");
        FileOutputStream prime = new FileOutputStream("D:\\PRIME.DAT");

        for (int i = 2; i <= 200; i++) {
            for (int j = 2; j <= i; j++) {
                if (j == i-1 || i == 2) {
//                    System.out.println(i);

                    //惯例：
                    //------------------------------------------
                    String msg = i + " ";
                    prime.write(msg.getBytes());
                    //------------------------------------------
                    break;
                }
                if (i % j == 0) {
                    break;
                }
            }
        }
        prime.close(); //在这才能关闭，而不是在循环中写一个关一下。即关闭和new同级
    }

    //8.检查C盘根目录下CONFIG.
    //9.SYS文件是否存在，若在则显示该文件的名称和内容。
    public static void t8t9() throws IOException {
        System.out.println("---------------8 & 9---------------");
        File config = new File("D:\\PRIME.DAT");

        if (config.exists()) {
            System.out.println("该文件存在。其名称和内容读取如下");
            System.out.println(config.getName());

            //惯例：
            //--------------------------------------------
            FileInputStream fis = new FileInputStream(config);
            byte[] data = new byte[(int) config.length()];
            fis.read(data);
            fis.close();
            String msg = new String(new String(data));
            //---------------------------------------------
            System.out.println(msg);
        } else {
            System.out.println("文件不存在。");
        }
    }

}