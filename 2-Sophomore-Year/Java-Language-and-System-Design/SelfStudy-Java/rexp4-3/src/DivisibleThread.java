import java.util.Random;

public class DivisibleThread extends Thread{
    @Override
    public void run() {

        //在另一线程中求100以内能被3整除的数，
        for (int i = 1; i <= 100; i++) {
            if (i % 3 == 0) {
                //输出数据时应有提示，指明哪个线程输出的数据。
                System.out.println(i + ":来自" + getName());
            }
        }
        //求出后休眠一个随机时间。
        Random random = new Random();
        int t = random.nextInt(10000);
         try {
            Thread.sleep(t);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
         System.out.println(getName() + "休眠了" + t + "单位时间后结束");
    }
}
