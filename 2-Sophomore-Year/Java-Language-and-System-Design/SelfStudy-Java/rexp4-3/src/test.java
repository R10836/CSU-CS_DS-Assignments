public class test {
    public static void main(String[] args) {
        PrimeThread t1 = new PrimeThread();
        DivisibleThread t2 =new DivisibleThread();

        t1.setName("求素数的线程");
        t2.setName("求能被3整除的数的线程");


        t1.start();
        t2.start();
    }
}
