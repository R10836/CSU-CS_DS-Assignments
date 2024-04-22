import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)) {
            System.out.println("请输入字符串： ");
            String str = sc.nextLine();
            // 大小写转换
            System.out.println("大小写转换后的字符串为： " + exChange(str));
            // 判断是否为回文
            System.out.println("是否为回文： " + ReverseStr(str));
            // 输入两个字符串，从第一个字符串中删除第二个字符串的内容
            System.out.println("请输入字符串2： ");
            String str2 = sc.nextLine();
            System.out.println("删除后，第一个字符串为：" + DeleteString(str, str2));
            // 删去所有重复的字符，每种字符只保留一个
            System.out.println("删去所有重复的字符: " + DeleteRepeatChar(str));
            // 统计一个字符串中给定字符串出现的频率
            System.out.println("请输入一个字符：（在" + str + "中）");
            String str3 = sc.nextLine();
            System.out.println(str3 + "出现的频率为: " + CharFrequency(str, str3));
            // 将一个表示十进制数的字符串转换为以逗号分隔的字符串，从右边开始每三个数字标一个逗号
            System.out.println("请输入一串数字： ");
            String str4 = sc.nextLine();
            System.out.println("分隔后的数字为: " + AddComma(str4));
        }
    }

    // exChange方法转换大小写
    public static String exChange(String str) {
        StringBuffer sb = new StringBuffer();
        if (str != null) {
            for (int i = 0; i < str.length(); i++) {
                char c = str.charAt(i);
                if (Character.isUpperCase(c)) {
                    sb.append(Character.toLowerCase(c));
                } else if (Character.isLowerCase(c)) {
                    sb.append(Character.toUpperCase(c));
                }
            }
        }
        return sb.toString();
    }

    // ReverseStr方法判断是否为回文
    public static boolean ReverseStr(String str) {
        char[] arrayA = str.toCharArray();
        int top = 0;
        int end = arrayA.length - 1;
        if (str.equals("") || str.equals(null)) // 判断非法输入
            return false;
        while (top < end) {
            if (arrayA[top++] != arrayA[end--])
                return false;
        }
        return true;
    }

    // DeleteString方法完成：输入两个字符串，从第一个字符串中删除第二个字符串的内容
    public static String DeleteString(String str, String str2) {
        str = str.replace("", "-"); // 用replace给每个字符间加个-
        String[] first = str.split("-");
        str2 = str2.replace("", "-"); // 同上
        String[] second = str2.split("-");

        for (int i = 0; i < first.length; i++) {
            for (int j = 0; j < second.length; j++) {
                if (first[i].equals(second[j])) {
                    str = str.replace(first[i], "");
                }
            }
        }
        // str=str.replace("-","");//删掉-
        return str.toString();
    }

    // DeleteRepeatChar方法删除str中的重复字符
    public static String DeleteRepeatChar(String str) {
        StringBuilder sc = new StringBuilder(str);
        for (int i = 0; i < sc.length() - 1; i++) {
            for (int j = i + 1; j < sc.length(); j++) {
                if (sc.charAt(i) == sc.charAt(j)) {
                    sc.deleteCharAt(j);
                    j--;
                }
            }
        }
        return sc.toString();
    }

    // CharFrequency方法统计一个字符串中给定字符串出现的频率
    public static int CharFrequency(String str, String str3) {
        int count = 0;
        while (str.indexOf(str3) >= 0) {
            str = str.substring(str.indexOf(str3) + str3.length());
            count++;
        }
        return count;
    }

    // 将一个表示十进制数的字符串转换为以逗号分隔的字符串，从右边开始每三个数字标一个逗号
    public static String AddComma(String str) {
        StringBuffer ac = new StringBuffer(str);
        for (int i = str.length() - 3; i >= 0; i -= 3) {
            ac.insert(i, ",");
        }
        return ac.toString();
    }
}
