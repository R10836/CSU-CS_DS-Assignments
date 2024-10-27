import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class HttpServer {
    public static void main(String[] args) {
        ServerSocket serverSocket = null;
        try {
            // 创建服务器套接字
            serverSocket = new ServerSocket(8080); // 创建服务器套接字，并绑定到端口8080
        } catch (IOException ioe) {
            ioe.printStackTrace();
            System.exit(0);
        }
        Socket socket = null;
        InputStream inputStream = null;
        OutputStream outputStream = null;
        while (true) {
            try {

                socket = serverSocket.accept(); // 接受客户端的连接请求，并创建与客户端通信的套接字
                inputStream = socket.getInputStream(); // 获取套接字的输入流，用于读取客户端发送的数据
                outputStream = socket.getOutputStream(); // 获取套接字的输出流，用于向客户端发送数据
                Request request = new Request(inputStream); // 实例化请求类
                Response response = new Response(outputStream, request); // 实例化应答类
                request.parse(); // 解析HTTP请求报文
                response.sendStaticSourse(); // 根据请求做响应应答,并发送相应的HTTP响应报文
                socket.close();

            } catch (IOException ioe) {
                ioe.printStackTrace();
            }
        }
    }
}
