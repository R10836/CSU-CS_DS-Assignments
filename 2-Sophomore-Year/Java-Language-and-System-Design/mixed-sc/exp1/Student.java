public class Student {
    private String sNO;  // 学号
    private String sName;  // 姓名
    private String sSex;  // 性别
    private int sAge;  // 年龄
    private double sJava;  // Java课程成绩
    
    public Student(String no, String name, String sex, int age, double java) {
        this.sNO = no;
        this.sName = name;
        this.sSex = sex;
        this.sAge = age;
        this.sJava = java;
    }
    
    public String getNo() {
        return this.sNO;
    }
    
    public String getName() {
        return this.sName;
    }
    
    public String getSex() {
        return this.sSex;
    }
    
    public int getAge() {
        return this.sAge;
    }
    
    public double getJava() {
        return this.sJava;
    }
}