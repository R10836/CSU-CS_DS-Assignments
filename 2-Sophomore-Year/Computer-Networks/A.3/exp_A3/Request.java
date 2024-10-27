import java.io.InputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;

public class Request {
    private InputStream inputStream = null;
    private String uri = null;

    public Request(InputStream inputStream) {
        // 获取输入流
        this.inputStream = inputStream;
    }
    // 解析请求报文
    public void parse() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(inputStream));
        String msg = br.readLine();
        // 在终端打印报文
        System.out.println(msg);
        // 解析请求文件名
        this.uri = msg.split(" ")[1].substring(1);
        while ((msg = br.readLine()) != null) {
            System.out.println(msg);
            if (msg.length() == 0) {
                break;
            }
        }
    }
    // 获取请求文件名
    public String getUri() {
        return this.uri;
    }
}
