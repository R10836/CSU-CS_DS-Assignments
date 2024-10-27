import javax.swing.*;
import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

// 继承自JFrame的服务器类来实现图形用户界面
public class Server extends JFrame implements Runnable {
    private ServerSocket ss = null; // ServerSocket对象，用于监听连接请求
    private JTextArea jta = new JTextArea(); // JTextArea对象，用于在界面上显示服务器日志
    private ArrayList<ChatThread> chatThread = new ArrayList<ChatThread>(); // ArrayList，用于存储正在运行的用户线程

    public Server() throws Exception {
        this.setTitle("服务器窗口");
        this.setSize(300, 400);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setVisible(true);
        this.add(jta, BorderLayout.NORTH);
        ss = new ServerSocket(8080);
        new Thread(this).start();
    /* 构造函数Server()用于初始化服务器对象。
    * 它设置了窗口的标题、大小、默认关闭操作，并将日志文本区域添加到界面上。
    * 然后，创建一个ServerSocket对象并开始在8080端口上监听连接请求。
    * 最后，启动一个新的线程来运行服务器。 */
    }

    // 重写run方法实现多线程
    public void run() {
        while (true) {
            try {

                Socket socket = this.ss.accept();
                BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                String msg;
                while ((msg = bufferedReader.readLine()) == null) {}

                jta.append(msg + "\n");

                sendMsg(msg);
                ParseMsg parseMsg = new ParseMsg(msg); // ParseMsg对象，解析msg
                ChatThread tmp = new ChatThread(parseMsg.getSourse(), parseMsg.getTarget(), socket);
                tmp.start();

                PrintStream printStream = new PrintStream(socket.getOutputStream());
                msg = ("UserName/");
                for (ChatThread i : chatThread) {
                    msg = msg + i.userName + "/";
                }
                printStream.println(msg);
                chatThread.add(tmp);

            } catch (IOException ioe) {
            }
        }
    }

    // 根据消息解析并按不同方式发送
    public void sendMsg(String msg) {
        ParseMsg parseMsg = new ParseMsg(msg); // ParseMsg对象，解析msg
        // 广播
        if (parseMsg.getMethod().equals("BROADCAST")) {
            broadcast(parseMsg.getMsg());
        // 群组
        } else if (parseMsg.getMethod().equals("GROUP")) {
            group(parseMsg.getTarget(), parseMsg.getMsg());
        // 点对点
        } else if (parseMsg.getMethod().equals("p2p")) {
            p2p(parseMsg.getTarget(), parseMsg.getMsg());
        // 用户退出
        } else if (parseMsg.getMethod().equals("LEAVE")) {
            for (ChatThread i : chatThread) {
                if (parseMsg.getSourse().equals(i.userName)) {
                    i.interrupt(); // 中断线程
                    chatThread.remove(i); // 从运行列表中移出
                    try {
                        // 关闭输入流、输出流、套接字
                        i.bufferedReader.close();
                        i.printStream.close();
                        i.socket.close();
                        break;
                    } catch (IOException ioe) {
                        ioe.printStackTrace();
                    }
                }
            }
            broadcast(parseMsg.getMsg()); // 广播用户离开信息
        }
    }

    // 广播
    public void broadcast(String msg) {
        for (ChatThread i : chatThread) {
            i.printStream.println(msg);
        }
    }

    // 群组
    public void group(String target, String msg) {
        for (ChatThread i : chatThread) {
            if (i.chatRoom.equals(target))
                i.printStream.println(msg);
        }
    }

    // 点对点
    public void p2p(String target, String msg) {
        for (ChatThread i : chatThread) {
            if (i.userName.equals(target)) {
                i.printStream.println(msg);
                break;
            }
        }
    }

    // 聊天线程类(与客户端的通信线程)
    class ChatThread extends Thread {
        String userName = null; // 客户端的用户名
        String chatRoom = null; // 客户端所属的聊天室名称
        Socket socket = null; // 与客户端进行通信的套接字
        BufferedReader bufferedReader = null; // 用于从套接字的输入流中读取客户端发送的数据
        PrintStream printStream = null; // 用于向套接字的输出流发送数据

        public ChatThread(String userName, String chatRoom, Socket socket) {
            this.userName = userName;
            this.chatRoom = chatRoom;
            this.socket = socket;
            try {
                this.bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                this.printStream = new PrintStream(socket.getOutputStream());
            } catch (IOException ioe) {
                ioe.printStackTrace();
            }
        }

        // 重写run方法，线程运行内容
        public void run() {
            // 不断从输入流中获取信息
            while (true) {
                try {
                    String msg = bufferedReader.readLine();
                    if (msg != null && !msg.equals("")) {
                        jta.append(msg + "\n");
                        sendMsg(msg);
                    }
                } catch (Exception e) {
                }
            }
        }

    }

    // main
    public static void main(String[] args) throws Exception {
        new Server();
    }
}