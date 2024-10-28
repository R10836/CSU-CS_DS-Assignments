/*
* 类的主要目的是提供一个简单的用户认证界面，并与服务器进行通信以实现用户登录功能。
* */

package Student;

import Student.Register;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.Socket;

class Login extends JFrame implements ActionListener {
    //声明网络通信用的PrintStream和BufferedReader对象，用于发送和接收数据。
    public PrintStream ps = null;
    public BufferedReader br = null;
    //创建文本框Id和密码框Passwd，分别用于输入账号和密码。
    private JTextField Id = new JTextField(20);
    private JPasswordField Passwd =new JPasswordField(20);
    private JLabel welcome = new JLabel("",JLabel.CENTER);
    private JLabel zhanghao = new JLabel("账号:");
    private JLabel mima = new JLabel("密码:");
    private JLabel Picture = new JLabel();
    //创建标签组件welcome、zhanghao、mima和Picture，用于显示欢迎信息、账号提示、密码提示和用户头像。
    private JButton Login_Button = new JButton("登录");
    private JButton Register_Button = new JButton("注册");
    //创建按钮Login_Button和Register_Button，分别用于登录和注册操作。
    private FileDialog dialog = null;
    private OutputStream out = null;

    public Login() throws Exception{
        this.setLayout(null);  //用绝对定位
        Font font = new Font("微软雅黑", Font.PLAIN, 25);
        welcome.setLocation(20,50);
        welcome.setSize(600,80);
        welcome.setFont(new Font("微软雅黑", Font.BOLD, 45));
        Id.setLocation(250,200);
        Id.setSize(300,60);
        Id.setFont(font);
        Passwd.setLocation(250,300);
        Passwd.setSize(300,60);
        Passwd.setFont(font);
        zhanghao.setLocation(180,190);
        zhanghao.setSize(200,80);
        zhanghao.setFont(new Font("微软雅黑", Font.BOLD, 25));
        mima.setLocation(180,290);
        mima.setSize(200,80);
        mima.setFont(new Font("微软雅黑", Font.BOLD, 25));
        ImageIcon image = new ImageIcon("");
        image.setImage(image.getImage().getScaledInstance(100,100,Image.SCALE_DEFAULT));  //创建缩放版本图像
        Picture = new JLabel(image);
        Picture.setLocation(60, 230);
        Picture.setSize(100, 100);
        Register_Button.setLocation(120,400);
        Register_Button.setSize(160,60);
        Register_Button.setFont(font);
        Register_Button.addActionListener(this);
        Login_Button.setLocation(300, 400);
        Login_Button.setSize(160,60);
        Login_Button.setFont(font);
        Login_Button.addActionListener(this);
        // Socket类被用来与本地（localhost）的服务器建立连接，端口号为10222。
        // 然后，通过Socket对象获取输出流out和输入流br，用于向服务器发送数据和从服务器接收数据。
        // 这些流在后续的登录操作中被用来发送用户输入的账号和密码，并接收服务器返回的验证结果。
        Socket s = new Socket("localhost", 10222);  //创建Socket连接到服务器，初始化输出流out、打印流ps和缓冲读取流br
        out = s.getOutputStream();
        ps = new PrintStream(out);
        br = new BufferedReader(new InputStreamReader(s.getInputStream()));
        //窗体基本设置  将所有组件添加到窗体，设置窗体标题、位置、大小、关闭操作和可见性
        this.add(welcome);
        this.add(Id);
        this.add(Picture);
        this.add(Passwd);
        this.add(zhanghao);
        this.add(mima);
        this.add(Login_Button);
        this.add(Register_Button);
        this.setTitle("欢迎登录");
        this.setLocation(200,100);
        this.setSize(600,550);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        if(e.getSource() == Register_Button){
            try{
                new Register(ps,br);  // 点击注册按钮，打开注册界面
            }catch(Exception exc){}
        }
        else {  // 点击登录按钮，检查输入是否为空，发送登录请求到服务器，处理服务器返回的信息并进行相应操作
                try{
                    String passwd1 = String.valueOf(Passwd.getPassword());
                    if(Id.getText().isEmpty()||passwd1.isEmpty()){
                        JOptionPane.showMessageDialog(this,"请检查账号或密码后重新输入!");
                    }else {
                        ps.println("LOGIN-" + Id.getText() + "-" + passwd1);
                        String message = br.readLine();
                        String[] msgs = message.split("-");
                        if (msgs[0].equals("OK")) {  //存在此人
                            String path = msgs[1];  //1是头像路径
                            new Student(Id.getText(),path,ps,br,out);
                            this.setVisible(false);
                        } else if(message.equals("CHONG")){ //已经登录过
                            JOptionPane.showMessageDialog(this, "此账户已经登录，不能重复登录!");
                        } else {
                            JOptionPane.showMessageDialog(this, "账号或密码错误，请重新输入!");
                        }
                    }
                }catch(Exception ex){}
            }
        }
    public static void main(String[] args) throws Exception{
        new Login();
    }
}