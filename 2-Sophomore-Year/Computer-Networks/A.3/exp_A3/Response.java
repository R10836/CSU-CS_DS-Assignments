import java.io.OutputStream;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class Response {
    private OutputStream outputStream;
    private Request request;

    public Response(OutputStream outputStream, Request request) {
        this.outputStream = outputStream;
        this.request = request;
    }

    public void sendStaticSourse() {
        BufferedOutputStream bos = new BufferedOutputStream(outputStream);
        BufferedInputStream bis = null;
        try {
            // 如果请求的文件存在
            if (new File(this.request.getUri()).exists()) {
                try {
                    // 获取文件输入流
                    bis = new BufferedInputStream(new FileInputStream(this.request.getUri()));
                } catch (FileNotFoundException fnfe) {
                }
                byte[] data = new byte[1024];
                int length = 0;
                // 发送可以发送文件的报文
                String msg = "HTTP/1.1 200 OK \r\n" +
                        "content-type: text/html; charset=utf-8 \r\n\r\n";
                // 发送文件数据
                bos.write(msg.getBytes());
                while ((length = bis.read(data)) != -1) {
                    bos.write(data, 0, length);
                }
            } else {
                // 发送未找到文件报文
                String errormsg = "HTTP/1.1 404 File Not Found\r\n" +
                        "Content-Type:text/html\r\n" +
                        "Content-Length:23\r\n" +
                        "\r\n" +
                        "<h2>File Not Found</h2>";
                bos.write(errormsg.getBytes());
            }
            // 关闭输出流
            bos.close();
            // 关闭输入流
            if (bis != null) {
                bis.close();
            }
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
    }
}