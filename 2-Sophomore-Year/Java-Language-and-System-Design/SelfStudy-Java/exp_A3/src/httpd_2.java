import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class httpd_2 {
    public static void main(String[] args) {
        Thread th1=new Thread(new ServerRunnable()),th2=new Thread(new KillerRunnable());
        th2.start();
        th1.start();
    }
}
class ServerRunnable implements Runnable {
    static ServerSocket sskt = null;
    static Socket Skt = null;
    static InputStream is = null;
    static OutputStream os = null;
    public void run(){
        try {
            // 创建服务器套接字
            sskt = new ServerSocket(80);
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(0);
        }
        while(true)
            try {
                Skt = sskt.accept();
                is = Skt.getInputStream();
                os = Skt.getOutputStream();
                Request rq = new Request(is);
                Response response = new Response(os, rq);
                response.sendStaticSourse();
            } catch (IOException e) {
                e.printStackTrace();
            } finally {
                try {Skt.close();}
                catch (Exception e) {}
                System.out.println("=======================================");
            }
    }
}
class KillerRunnable implements Runnable {
    Scanner in=new Scanner(System.in);
    public void run(){
        if(in.next().charAt(0)=='s'){
            System.out.println("shutting down! ");
            try{ServerRunnable.sskt.close();}catch(IOException e){}
            System.exit(0);
        }
    }
}
class Response {
    private OutputStream os=null;
    private String uri="";
    static String curPath="C:\\OD\\Schoolwork\\Network\\WebServer\\";
    static{
        if (new File("index.html").exists()){curPath="";}
    }

    public Response(OutputStream OS, Request RQ) {
        this.os = OS;
        this.uri = RQ.getUri();
    }

    public void sendStaticSourse() {
        BufferedOutputStream bos = new BufferedOutputStream(os);
        BufferedInputStream bis = null;

        System.out.println("Requested Found: "+uri);
        String LocalURI=new File(curPath+uri).isDirectory()?(curPath+uri+"index.html"):curPath+uri;
        // String LocalURI=new File(curPath+uri).isDirectory()?(curPath+uri+"index.html"):(new File(curPath+uri+"\\").isDirectory()?(curPath+uri+File.pathSeparator+"index.html"):curPath+uri);/* 预计使用这一段来达到不加“/”而识别路径额目的，然而没有成功 */
        try {
            // 如果请求的文件存在

            if (new File(LocalURI).exists()) {
                System.out.println("Requested file found! ");
                try {
                    bis = new BufferedInputStream(new FileInputStream(LocalURI));
                } catch (FileNotFoundException e) {}
                byte[] data = new byte[1024];
                int length = 0;
                String msg = "HTTP/1.1 200 OK \r\n"+"content-type: text/html; charset=utf-8 \r\n\r\n";
                // 发送文件数据
                bos.write(msg.getBytes());
                while ((length = bis.read(data)) != -1) {
                    bos.write(data, 0, length);
                }
            } else {
                System.err.println("Requested file NOT found! ");
                String errormsg = "HTTP/1.1 404 File Not Found\r\n"+"Content-Type:text/html\r\n"+"Content-Length:"+(uri.length()+50)+"\r\n"+"\r\n"+"<h2><span style=\"color:red;\">"+uri+"</span> Not Found</h2>";
                bos.write(errormsg.getBytes());
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try{
                bos.close();
            }
            catch (Exception e) {}
            try{
                bis.close();
            }
            catch (Exception e) {}
        }
    }
}
class Request {
    private InputStream is = null;
    private String uri = "";

    public Request(InputStream IS) {
        this.is = IS;
        try{
            BufferedReader br = new BufferedReader(new InputStreamReader(is));
            String msg = br.readLine();
            this.uri = msg.split(" ")[1].substring(1);
            // if (this.uri.equals("")){
            //     this.uri="index.html";
            // }/* 最初利用此段实现对一个光头ip地址的解析，现在在响应中实现 */
            while ((msg = br.readLine()) != null) {
                // System.out.println(msg);
                if (msg.length() == 0) {
                    break;
                }
            }
        }
        catch (IOException e) {}
    }
    public String getUri(){
        return this.uri;
    }
}

