import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;

// 用户类
public class Client extends JFrame implements Runnable, ActionListener, WindowListener {
    private String userName; // 客户端的用户名
    private String chatRoom; // 客户端所属的聊天室名称
    private Socket socket; // 用于与服务器建立连接
    private PrintStream ps = null; // 用于向服务器发送数据
    private BufferedReader bf = null; // 用于从服务器接收数据
    private JTextField jtf = new JTextField(); // 声明一个文本框 jtf，用于输入要发送的消息
    private JTextArea jta = new JTextArea(); // 声明一个文本区域 jta，用于显示接收到的消息
    private JComboBox<String> jcb = new JComboBox<String>(new String[] { "Server" }); // 声明一个下拉列表框 jcb，用于选择消息的目标（发送给服务器还是聊天室中的其他成员）

    // 构造函数用于初始化类的成员变量，并创建用户界面
    public Client(String userName, String chatRoom, Socket socket) throws Exception {
        this.userName = userName;
        this.chatRoom = chatRoom;
        jcb.addItem(this.chatRoom);
        this.setTitle(userName + "-已连接");
        this.setSize(400, 400);
        this.setDefaultCloseOperation(HIDE_ON_CLOSE);
        this.setVisible(true);
        this.add(jtf, BorderLayout.SOUTH);
        this.add(jta, BorderLayout.CENTER);
        this.add(jcb, BorderLayout.NORTH);
        bf = new BufferedReader(new InputStreamReader(socket.getInputStream())); // 将套接字的输入流转换为字符流，用于从服务器接收数据
        ps = new PrintStream(socket.getOutputStream()); // 将套接字的输出流用于向服务器发送数据
        ps.println("BROADCAST/" + userName + "/" + chatRoom + "/" + userName + "已进入" + chatRoom + "\n"); // 向服务器发送一条消息，通知服务器当前用户已进入聊天室
        jtf.addActionListener(this); // 事件监听器
        this.addWindowListener(this); // 窗口监听器
        new Thread(this).start(); // 启动线程
    }

    // 线程运行内容
    public void run() {
        while (true) {
            try {
                String msg = bf.readLine();

                // case1新用户进入聊天室。检查消息中是否包含"已进入"，即检查是否有新用户加入聊天室。
                if (msg.indexOf("已进入") != -1) {
                    jcb.addItem(msg.split("已进入")[0]); // 将新加入的用户的用户名添加到下拉列表框jcb中
                    jta.append(msg + "\n"); // 将接收到的消息追加到文本区域jta中
                }
                // case2用户离开聊天室。检查消息中是否包含"已离开"，即检查是否有用户离开聊天室。
                else if (msg.indexOf("已离开") != -1) {
                    jcb.removeItem(msg.split("已离开")[0]);
                    jta.append(msg + "\n");
                }
                // case3接收已经在聊天室的用户信息。检查消息是否以 "UserName"开头，即接收已经在聊天室的用户信息。
                else if (msg.startsWith("UserName")) {
                    String[] parse = msg.split("/"); // 将消息按照 "/" 进行拆分，并存储到parse数组中。
                    for (int i = 1; i < parse.length; i++) {
                        jcb.addItem(parse[i]); // 将遍历到的用户名添加到下拉列表框jcb中，即添加已经在聊天室的其他用户。
                    }
                }
                // case4如果以上条件都不满足，即接收到的消息为普通的聊天消息。
                else {
                    jta.append(msg + "\n"); // 将接收到的消息追加到文本区域jta中
                }

            } catch (Exception e) {
            }
        }
    }

    // 根据发送方法发送信息（根据下拉列表框的内容确定发送方式：广播消息、群组消息还是点对点消息。）
    public void sendmsg(String msg) {
        // 如果是广播。通过输出流 ps 向服务器发送广播消息。消息格式为 "BROADCAST/用户名/Server/消息内容"
        if (jcb.getSelectedItem().equals("Server")) {
            ps.println("BROADCAST/" + userName + "/Server/" + msg);
        }
        // 如果是组播。通过输出流ps向聊天室中的其他成员发送群组消息。消息格式为 "GROUP/用户名/聊天室名称/消息内容"。
        else if (jcb.getSelectedItem().equals(this.chatRoom)) {
            ps.println("GROUP/" + userName + "/" + this.chatRoom + "/" + msg);
        }
        // 如果其他情况（p2p）。通过输出流 ps 向选择的目标发送点对点消息。消息格式为 "p2p/用户名/目标用户名/消息内容"。
        else {
            ps.println("p2p/" + userName + "/" + jcb.getSelectedItem() + "/" + msg);
        }
    }

    // 如果发送信息，根据下拉列表框内容确定发送方式
    public void actionPerformed(ActionEvent e) {    // actionPerformed方法是ActionListener接口的实现方法，用于处理用户在文本框中输入并按下回车键时的操作

        String msg = new String(this.userName + "对");
        /* （客户名）对 */

        if (jcb.getSelectedItem().equals("Server")) {
            msg += "所有人说：";
            /* （客户名）对所有人说： */
        } else if (jcb.getSelectedItem().equals(this.chatRoom)) {
            msg += "聊天室" + this.chatRoom + "中的所有人说：";
            /* （客户名）对聊天室（聊天室名）中的所有人说： */
        } else {
            msg += jcb.getSelectedItem() + "说：";
            /* （客户名）对（客户2名）说： */
        }

        if (!jcb.getSelectedItem().equals("Server") && !jcb.getSelectedItem().equals(this.chatRoom)) { // p2p
            jta.append(msg + ":" + jtf.getText() + "\n");
        }

        sendmsg(msg + jtf.getText() + "\n"); // 将拼接好的消息字符串和文本框中输入的内容发送给选择的目标
        jtf.setText("");

        /*
         actionPerformed方法根据用户选择的目标和文本框中的输入内容，构造相应的消息字符串，
         并将该消息字符串发送给服务器或聊天室中的其他成员。
         然后，将消息内容追加到文本区域 jta 中供用户查看，并清空文本框的内容，以便下次输入。
         */
    }

    public void windowActivated(WindowEvent e) {

    }

    // 如果窗口关闭，则发送用户离开信息
    public void windowClosing(WindowEvent e) { // windowClosing方法是WindowListener接口的实现方法，用于处理窗口关闭事件。
        // 通过输出流 ps 向服务器发送用户离开的消息。消息格式为 "LEAVE/用户名/聊天室名称/用户已离开聊天室"
        ps.println("LEAVE/" + this.userName + "/" + this.chatRoom + "/" + this.userName + "已离开" + this.chatRoom + "\n");
        this.ps.close();
        try {
            this.bf.close();
        } catch (IOException ioe) {
            ioe.printStackTrace();
        }
        this.dispose();
        System.exit(0);
    }

    public void windowClosed(WindowEvent e) {

    }

    public void windowIconified(WindowEvent e) {

    }

    public void windowOpened(WindowEvent e) {

    }

    public void windowDeiconified(WindowEvent e) {

    }

    public void windowDeactivated(WindowEvent e) {

    }

}

