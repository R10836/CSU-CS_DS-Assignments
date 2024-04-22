import java.util.Random;

class PrimeNumberThread extends Thread{
    public Object start;
    private String ThreadName1;
    Random r=new Random();
    int t1=r.nextInt(10000);
    public PrimeNumberThread(String ThreadName1){
        this.ThreadName1=ThreadName1;
    }
    public void run(){
        System.out.println("线程"+ThreadName1);
        int i,j;
        for(i=1;i<=100;i++) {
            if (i == 1 || i == 2) {
                System.out.print(i+" ");
                continue;
            }
            for (j = 2; j < i; j++) {
                if (i % j == 0)
                    break;
                if (j == i - 1)
                    System.out.print(i+" ");
            }
        }
        System.out.println();
        try{
            Thread.sleep(t1);
        }
        catch(Exception ex){}
        System.out.println(ThreadName1+"执行完毕");
    }

}
class DivideThreeThread extends Thread{
    public Object start;
    private String ThreadName2;
    Random r=new Random();
    int t2=r.nextInt(10000);
    public DivideThreeThread(String ThreadName2){
        this.ThreadName2=ThreadName2;
    }
    public void run(){
        System.out.println("线程"+ThreadName2);
        int i;
        for(i=1;i<=100;i++) {
                if (i % 3 == 0)
                    System.out.print(i+" ");
        }
        System.out.println();
        try{
            Thread.sleep(t2);
        }
        catch(Exception ex){}
        System.out.println(ThreadName2+"执行完毕");
    }

}
public class test2 {
    public static void main(String[]args)throws Exception{
        PrimeNumberThread n1=new PrimeNumberThread("素数");
        DivideThreeThread d1=new DivideThreeThread("被3整除");
        n1.start();
        d1.start();

    }
}