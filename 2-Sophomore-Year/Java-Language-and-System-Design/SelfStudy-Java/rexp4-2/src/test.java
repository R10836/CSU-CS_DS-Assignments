public class test {
    public static void main(String[] args) {
        MyThread t1 = new MyThread();
        MyThread t2 = new MyThread();
        MyThread t3 = new MyThread();
        t1.setName("线程1");
        t2.setName("线程2");
        t3.setName("线程3");
        // start方法表示开启线程
        t1.start();
        t2.start();
        t3.start();
    }
}