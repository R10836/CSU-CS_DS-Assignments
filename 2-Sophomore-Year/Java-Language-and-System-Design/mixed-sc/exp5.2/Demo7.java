import java.io.*;

public class Demo7 {
    private Isprim sushu = null;
    FileOutputStream fos = null;
    public Demo7() {
        try {
            fos = new FileOutputStream("D://prime.dat");
            sushu = new Isprim();
            for(int i=2;i<=200;i++)
            {
                if(sushu.isPrim(i)){
                    fos.write(i);
                    System.out.println(i);
                }
            }
            fos.close();
        } catch (FileNotFoundException e) {
            System.out.println("找不到指定文件"); System.exit(-1);
        }catch (IOException e){
            System.out.println("文件写入错误"); System.exit(-1);
        }
        System.out.println("文件写入完毕！");
    }
    public static void main(String[] args) {
        Demo7 tip = new Demo7();
    }
//定义Isprime类用于判断一个数是否是素数
    class Isprim {
        public Isprim(){
        }
        public boolean isPrim(int m)
        {
            int i=2;
            boolean flag=true;
            while(true)
            {
                if(m%i==0)
                {
                    flag=false;
                    break;
                }
                i++;
            }
            return flag;
        }

    }

}
