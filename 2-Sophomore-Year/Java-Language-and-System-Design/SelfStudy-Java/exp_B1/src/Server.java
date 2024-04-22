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

                Socket socket = this.ss.accept(); // 接受客户端的连接请求，并返回一个与客户端通信的套接字(socket)。
                BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream())); //将字节流转化为字符流，再放入BufferedReader。从套接字的输入流读取客户端发送的数据。
                String msg;
                while ((msg = bufferedReader.readLine()) == null) {}// 等待读取到有效的消息为止

                jta.append(msg + "\n"); // 将读取到的消息追加到服务器日志文本区域jta中

                sendMsg(msg);
                ParseMsg parseMsg = new ParseMsg(msg); // 自创ParseMsg对象，解析msg
                ChatThread tmp = new ChatThread(parseMsg.getSourse(), parseMsg.getTarget(), socket); // 根据用户名、聊天室名称、套接字创建用户聊天线程。ChatThread的对象tmp即表示与客户端的通信线程。
                tmp.start(); // 开启此线程

                PrintStream printStream = new PrintStream(socket.getOutputStream()); // 创建一个 PrintStream 对象，使用套接字的输出流作为输出目标。这样，printStream就可以通过print()、println()等方法将数据发送到客户端。
                msg = ("UserName/");
                for (ChatThread i : chatThread) {
                    // 遍历每个ChatThread对象，将每个ChatThread对象的用户名i.userName追加到msg中，并在每个用户名后面添加一个斜杠"/"，用于分隔不同的用户名
                    // 形成一个以 "UserName/" 开头的消息字符串。这个消息字符串用于向客户端发送服务器的用户情况，以告知客户端当前连接到服务器的用户名列表。
                    msg = msg + i.userName + "/";
                }
                printStream.println(msg); // 将构建好的消息字符串发送到客户端，通知客户端服务器上的用户名列表。
                chatThread.add(tmp); // 将ChatThread对象tmp添加到服务器的用户线程列表chatThread中，用于跟踪管理当前运行的用户线程。

            } catch (IOException ioe) {
            }
        }
    }

    // 根据消息解析并按不同方式发送
    public void sendMsg(String msg) {
        ParseMsg parseMsg = new ParseMsg(msg); // 自创ParseMsg对象，解析msg
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
            // 遍历存储在chatThread列表中的每个ChatThread对象
            // 对于每个ChatThread对象i，通过其关联的PrintStream对象的println()方法，向客户端发送消息msg
            i.printStream.println(msg);
        }
    }

    // 群组
    public void group(String target, String msg) {
        for (ChatThread i : chatThread) {
            // 对于每个 ChatThread 对象 i，检查它的 chatRoom 属性是否与目标群组 target 相匹配
            // 如果 i 的 chatRoom 属性与目标群组 target 相匹配，那么通过 i 对应的 PrintStream 对象的 println() 方法，向客户端发送消息 msg
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
                    String msg = bufferedReader.readLine(); // 从输入流中读取一行消息，并将其存储在变量msg中
                    if (msg != null && !msg.equals("")) {
                        jta.append(msg + "\n"); // 将读取到的消息追加到服务器的日志文本区域（jta）中
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