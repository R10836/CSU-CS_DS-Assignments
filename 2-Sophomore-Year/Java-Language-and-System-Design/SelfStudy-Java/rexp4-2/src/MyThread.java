import java.util.Random;

public class MyThread extends Thread{
    @Override
    public void run() throws RuntimeException {
        System.out.println(getName() + "已经创建。");

        Random random = new Random();
        int t = random.nextInt(10000);
        try {
            Thread.sleep(t);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        System.out.println(getName() + "已经结束。休眠单位时长为：" + t);
    }
}
