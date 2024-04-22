interface StudentInterface{
    int setfee(int fe);
    int getfee();
}
interface TeacherInterface{
    int setpay(int pa);
    int getpay();
}
public class Graduate implements StudentInterface,TeacherInterface{
    String name;
    String sex;
    int age;
    int fee;
    int pay;
    Graduate(String gname,String gsex,int gage){
        name=gname;
        sex=gsex;
        age=gage;
    }
    public int setfee(int fe){
        fee=fe;return fee;
    }
    public int getfee(){
        return fee;
    }
    public int setpay(int pa){
        pay=pa;return pay;
    }
    public int getpay(){
        return pay;
    }
    public int tuition(){
        return fee*2;
    }
    public int income(){
        return pay*12;
    }
}