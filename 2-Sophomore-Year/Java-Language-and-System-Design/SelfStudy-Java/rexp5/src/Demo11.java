import java.io.*;

public class Demo11 {
    public static void main(String[] args) throws Exception {
        Object[] obj = dser();
        Student stuMax = (Student) obj[0];
        for (int i = 0; i < obj.length; i++) {
            Student student = (Student) obj[i];
            if ((student.getEnglish()+student.getMath()+student.getEnglish())/3.0> (stuMax.getChinese()+stuMax.getMath()+stuMax.getEnglish())/3.0) {
                stuMax = student;
            }
        }
        System.out.println("学号："+stuMax.getId()+" 姓名："+stuMax.getName() + " 语文成绩：" + stuMax.getChinese() + " 数学成绩：" + stuMax.getMath() + " 英语成绩：" + stuMax.getEnglish());
    }
    public static Object[] dser() throws Exception {
        File file = new File("d:\\STUDENT.DAT");
        ObjectInputStream ois = null;
        InputStream input = new FileInputStream(file);
        ois = new ObjectInputStream(input);
        Object[] obj = (Object[]) ois.readObject();
        ois.close();
        return obj;
    }
}