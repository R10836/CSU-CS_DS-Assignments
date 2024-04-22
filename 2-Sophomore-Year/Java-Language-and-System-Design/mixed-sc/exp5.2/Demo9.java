import java.io.*;

public class Demo9 {
    public static void main(String[] args) throws Exception {
        Student[] students = {new Student("001", "张三", 89, 90, 91),
                new Student("002", "李四", 92, 93, 94),
                new Student("003", "王五", 95, 96, 97),
                new Student("004", "赵六", 98, 99, 100),
                new Student("005", "田七", 100, 100, 100)};
        ser(students);
    }

    public static void ser(Object obj[]) throws Exception {
        File file = new File("d:\\STUDENT.DAT");
        ObjectOutputStream oos = null;
        OutputStream out = new FileOutputStream(file);
        oos = new ObjectOutputStream(out);
        oos.writeObject(obj);
        oos.close();
    }
}

class Student implements Serializable {
    private String id;
    private String name;
    private int chinese;
    private int math;
    private int english;

    public Student() {
    }

    public Student(String id, String name, int chinese, int math, int english) {
        this.id = id;
        this.name = name;
        this.chinese = chinese;
        this.math = math;
        this.english = english;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getChinese() {
        return chinese;
    }

    public void setChinese(int chinese) {
        this.chinese = chinese;
    }

    public int getMath() {
        return math;
    }

    public void setMath(int math) {
        this.math = math;
    }

    public int getEnglish() {
        return english;
    }

    public void setEnglish(int english) {
        this.english = english;
    }
}
