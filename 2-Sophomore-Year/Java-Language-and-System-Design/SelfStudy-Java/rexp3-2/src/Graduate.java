public class Graduate implements StudentInterface, TeacherInterface{
    private String name;
    private String sex;
    private int age;
    private int fee;
    private int pay;


    public Graduate(){

    }

    public Graduate(String name, String sex, int age){
        this.name = name;
        this.sex = sex;
        this.age = age;
    }

    @Override
    public void setFee(int fee){
        this.fee = fee;
    }

    @Override
    public int getFee(){
        return this.fee;
    }

    @Override
    public void setPay(int pay) {
        this.pay = pay;
    }

    @Override
    public int getPay() {
        return this.pay;
    }
}