import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class Demo8 {
    public static void main(String[] args) throws IOException {
        File file=new File("D:\\CONFIG.SYS");
        if (file.exists()){
            FileInputStream fi=null;
            try {
                System.out.println("文件存在");
                fi=new FileInputStream(file);
                byte[] date=new byte[1024];
                int hasRead;
                while ((hasRead=fi.read(date))>0){
                    System.out.println(new String(date,0,hasRead));
                }
            }catch (IOException e){
                e.printStackTrace();
            }finally {
                fi.close();
            }
        }else{
            System.out.println("文件不存在");
        }
    }
}