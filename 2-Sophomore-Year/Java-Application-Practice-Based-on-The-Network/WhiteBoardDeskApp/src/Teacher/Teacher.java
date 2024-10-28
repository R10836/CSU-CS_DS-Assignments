/*
* 用于教师与学生之间的远程教学交流和协作，提供了多种实时互动和教学工具支持
*
* 主要功能包括：

    1 界面设计：使用Swing组件设计教师端的用户界面，包括绘图板、功能按钮、颜色选择、在线学生列表、聊天记录显示等。

    2 数据库连接：通过JDBC连接MySQL数据库，实现教师和学生用户的登录验证、注册功能，并管理用户信息。

    3 Socket通信：使用Socket和ServerSocket实现基于TCP/IP的通信，教师端通过ServerSocket监听端口，接收学生端的连接请求，实现实时的消息传递和绘图同步功能。

    4 功能实现：
        绘图功能：支持直线、圆形、矩形、铅笔、画笔等绘制工具，教师绘制的图形可以实时同步到学生端。
        消息发送：教师可以群发消息给所有在线学生，包括文字消息和文件传输。
        在线学生管理：实时显示当前在线学生列表，教师可以对特定学生发送提醒消息。

    5 多线程处理：每个学生连接对应一个ChatThread线程处理通信和消息转发，确保多用户同时连接时的并发处理能力。
*  */

package Teacher;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;

class Teacher extends JFrame implements Runnable,ActionListener, MouseListener, MouseMotionListener {
    private static String url = "jdbc:mysql://localhost:3306/login?useSSL=false&allowPublicKeyRetrieval=true&serverTimezone=UTC";    //连接数据库的url,login是数据库名
    private static String user = "";
    private static String pass = "";
    private static Connection con;

    private JLabel explain = new JLabel("在线学生",JLabel.CENTER);
    private List users = new List();
    private JButton Send_Button = new JButton("发送消息");
    private JButton Send_File = new JButton("发送文件");
    private JButton Send_Remind = new JButton("提醒听课");
    private JTextField Sendword = new JTextField(20);       //发文字区域
    private JTextArea Chat = new JTextArea(10,45);     //聊天记录显示
    private ServerSocket ss = null;
    private Font font = new Font("微软雅黑", Font.PLAIN, 14);
    private HashMap<String,ChatThread> users_connect = new HashMap<String,ChatThread>();
    private JPanel paintBoard = new JPanel();   //画图板
    private JPanel buttonBoard=new JPanel();    //按钮面板
    private JPanel jpRight=new JPanel();        //绘画面板
    private JLabel exp1 = new JLabel("白板桌面程序",JLabel.CENTER);
    private JLabel exp2 = new JLabel("RuShawn 24-6",JLabel.CENTER);
    private boolean chongfu = true;
    private String Record_path = null;
    private InputStream in = null;
    private ServerFileThread serverFileThread = null;
    private int[] shapePoint=new int[4];        //设置绘制图形的四个点
    private Graphics2D g2d;                  //Graphics2D类型的画笔
    private String nowButton = "铅笔";       //用于记录当前使用的是哪个按钮，在画板上进行相应操作，默认为铅笔
    private String Now_color = "BLACK";     //设置默认值为黑色，该变量用于后来学生进入课堂时给与其教师画笔颜色

    //初始化整个教师端应用程序的界面和各个组件
    public Teacher() throws Exception{
        this.setLayout(null);
        Class.forName("com.mysql.cj.jdbc.Driver");  //Class.forName：查找并加载指定的类,加载数据库连接驱动并连接
        con = DriverManager.getConnection(url,user,pass);
        paintBoard.setBounds(500,0,598,598);
        paintBoard.setBackground(Color.white);  //背景白色
        paintBoard.addMouseListener(this);
        paintBoard.addMouseMotionListener(this);
        buttonBoard.setBounds(1100,90,85,120);
        buttonBoard.setLayout(new GridLayout(6,1));  //设置为网格布局
        //添加功能按钮
        String[] buttonNames={"直线","圆形","矩形","铅笔","画笔","清空"};
        JButton[] jbtList=new JButton[buttonNames.length];
        for(int i=0;i<buttonNames.length;i++){
            jbtList[i]=new JButton(buttonNames[i]);
            jbtList[i].setFont(new Font("微软雅黑", Font.PLAIN, 12));
            jbtList[i].setActionCommand(buttonNames[i]);    //设置图标触发的操作事件的命令名称
            jbtList[i].addActionListener(this);           //添加监听
            buttonBoard.add(jbtList[i]);
        }
        jpRight.setBounds(1100,210,85,75);     //绘图面板
        jpRight.setLayout(new GridLayout(3,2));        //设置为网格布局
        //添加颜色按钮
        Color[] colors={Color.red,Color.yellow,Color.blue,Color.green,Color.black,Color.white};
        String[] colorButtonNames={"红","黄","蓝","绿","黑","白"};
        JButton[] CjbtList=new JButton[colorButtonNames.length];
        for(int i=0;i<colorButtonNames.length;i++){
            CjbtList[i]=new JButton();
            CjbtList[i].setActionCommand(colorButtonNames[i]);
            CjbtList[i].setBackground(colors[i]);
            CjbtList[i].addActionListener(this);     //添加监听
            jpRight.add(CjbtList[i]);
        }
        //以下为其他控件布局
        explain.setSize(100,20);       //在线学生四个字
        explain.setLocation(1093,285);
        explain.setFont(new Font("微软雅黑", Font.BOLD, 15));
        users.setSize(86,200);
        users.setLocation(1099,305);
        users.setFont(new Font("Consolas", Font.PLAIN, 15));
        Sendword.addActionListener(this);
        Sendword.setLocation(0,500);
        Sendword.setSize(300,60);
        Sendword.setFont(new Font("微软雅黑", Font.PLAIN, 20));
        Send_Button.addActionListener(this);
        Send_Button.setSize(67,60);
        Send_Button.setLocation(300,500);
        Send_Button.setFont(new Font("微软雅黑", Font.PLAIN, 14));
        Send_Button.setMargin(new Insets(0,0,0,0));   //设置按钮边框和标签之间空白为0
        Send_File.addActionListener(this);
        Send_File.setSize(67,60);
        Send_File.setLocation(367,500);
        Send_File.setFont(font);
        Send_File.setMargin(new Insets(0,0,0,0));   //设置按钮边框和标签之间空白为0
        Send_Remind.addActionListener(this);
        Send_Remind.setSize(66,60);
        Send_Remind.setLocation(434,500);
        Send_Remind.setFont(font);
        Send_Remind.setMargin(new Insets(0,0,0,0));   //设置按钮边框和标签之间空白为0
        Chat.setFont(new Font("微软雅黑", Font.PLAIN, 15));
        Chat.setLineWrap(true);         //设置自动换行
        Chat.setLocation(0,0);
        Chat.setEditable(false);        //聊天记录无法编辑
        Chat.setMargin(new Insets(7, 7, 7, 7));     //设置7mm边距
        JScrollPane jsp = new JScrollPane(Chat);         //设置一个滚动条
        jsp.setBounds(0,0,500,500);
        ImageIcon image = new ImageIcon("");  //将图片路径作为参数传入
        image.setImage(image.getImage().getScaledInstance(85,90,Image.SCALE_DEFAULT));  //创建缩放版本图像
        JLabel Picture = new JLabel(image);
        Picture.setLocation(1100,0);
        Picture.setSize(85,90);
        exp1.setSize(100,20);     //好友列表四个字
        exp1.setLocation(1093,510);
        exp1.setFont(new Font("微软雅黑", Font.BOLD, 11));
        exp2.setSize(100,20);     //好友列表四个字
        exp2.setLocation(1093,530);
        exp2.setFont(new Font("微软雅黑", Font.BOLD, 11));
        this.setTitle("教师端");
        this.add(paintBoard);
        this.add(buttonBoard);
        this.add(jpRight);
        this.add(explain);
        this.add(users);
        this.add(Sendword);
        this.add(Send_Button);
        this.add(Send_File);
        this.add(Send_Remind);
        this.add(exp1);
        this.add(exp2);
        this.add(jsp);
        this.add(Picture);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setSize(1200,598);
        this.setVisible(true);
        Graphics g = paintBoard.getGraphics();         //获取画笔
        g2d=(Graphics2D) g;      //将Graphics转为Graphics2D
        g2d.setStroke(new BasicStroke(3.0f));   //设置画笔宽度
        //监听ServerSocket，接受学生端的连接请求，并启动新线程处理每个学生的通信
        ss = new ServerSocket(10222);    //信息传送使用端口
        new Thread(this).start();
    }

    //MouseListener中的方法。实现了MouseListener接口，用于记录鼠标按下时的坐标，用于绘图功能中的形状绘制起始点记录。
    public void mousePressed(MouseEvent e) {
        //记录鼠标按下的坐标
        shapePoint[0]=e.getX();
        shapePoint[1]=e.getY();
    }

    //实现了MouseListener接口，用于记录鼠标释放时的坐标，用于绘图功能中的形状绘制结束点记录，并根据当前选择的绘图工具绘制对应的图形。
    public void mouseReleased(MouseEvent e) {
        //记录鼠标松开的坐标
        shapePoint[2]=e.getX();
        shapePoint[3]=e.getY();
        //判断最后按下的是哪个图形按钮
        switch(nowButton){
            case "直线":
                //绘制直线
                g2d.drawLine(shapePoint[0],shapePoint[1],shapePoint[2],shapePoint[3]);
                //调用发送图形方法
                sendShape();
                break;
            case "圆形":
                //记录圆形左上角坐标点，并计算其宽高
                int x1=Math.min(shapePoint[0],shapePoint[2]);
                int y1=Math.min(shapePoint[1],shapePoint[3]);
                int width=Math.abs(shapePoint[0]-shapePoint[2]);
                int height=Math.abs(shapePoint[1]-shapePoint[3]);
                shapePoint[0]=x1;
                shapePoint[1]=y1;
                shapePoint[2]=width;
                shapePoint[3]=height;
                //绘制椭圆
                g2d.fillOval(shapePoint[0],shapePoint[1],shapePoint[2],shapePoint[3]);
                //调用发送图形方法
                sendShape();
                break;
            case "矩形":
                x1=Math.min(shapePoint[0],shapePoint[2]);
                y1=Math.min(shapePoint[1],shapePoint[3]);
                width=Math.abs(shapePoint[0]-shapePoint[2]);
                height=Math.abs(shapePoint[1]-shapePoint[3]);
                shapePoint[0]=x1;
                shapePoint[1]=y1;
                shapePoint[2]=width;
                shapePoint[3]=height;
                g2d.fillRect(shapePoint[0],shapePoint[1],shapePoint[2],shapePoint[3]);
                sendShape();
                break;
        }
    }

    //绘制铅笔的方法。实现了MouseMotionListener接口，用于处理鼠标拖动事件，主要用于铅笔和画笔功能中的连续绘制操作。
    public void mouseDragged(MouseEvent e) {
        if(nowButton.equals("铅笔") || nowButton.equals("画笔")){
            shapePoint[2]=shapePoint[0];
            shapePoint[3]=shapePoint[1];

            shapePoint[0]=e.getX();
            shapePoint[1]=e.getY();

            g2d.drawLine(shapePoint[0],shapePoint[1],shapePoint[2],shapePoint[3]);

            sendShape();
        }
    }

    //以下均为重写方法
    public void mouseMoved(MouseEvent e) {}
    public void mouseClicked(MouseEvent e) {}
    public void mouseEntered(MouseEvent e) {}
    public void mouseExited(MouseEvent e) {}

    //实现了ActionListener接口，处理用户界面中各个按钮的点击事件
    public void actionPerformed(ActionEvent e){
        if(e.getSource() == Sendword || e.getSource() == Send_Button){
            //群发消息按钮
            for(String ct : users_connect.keySet()){    //利用key值遍历哈希表
                users_connect.get(ct).Send.println("教师 "+new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date()));
                users_connect.get(ct).Send.println(Sendword.getText());
            }
            String sim = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
            Chat.append("教师 "+ sim +"\n");
            Chat.append(Sendword.getText()+"\n");
            Sendword.setText("");       //清空输入框
        }else if(e.getSource() == Send_File){
            FileDialog fLoader = new FileDialog(this,"选择打开的文件",FileDialog.LOAD);
            fLoader.setVisible(true);
            String path = fLoader.getDirectory() + fLoader.getFile();
            FileReadAndWrite.outFileToClient(path);    //将文件分发给学生端
            //群发消息按钮
            for(String ct : users_connect.keySet()){    //利用key值遍历哈希表
                users_connect.get(ct).Send.println("教师 "+new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date()));
                users_connect.get(ct).Send.println("[文件接收提醒]发送了一个文件。");
            }
            String sim = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
            Chat.append("教师 "+ sim +"\n");
            Chat.append("[文件接收提醒]发送了一个文件。\n");
        }else if(e.getSource() == Send_Remind){
            //提醒认真听课
            String selectedUser = users.getSelectedItem();
            String msg = "CARE";
            ChatThread ct = users_connect.get(selectedUser);
            ct.Send.println(msg);       //CARE提醒
            String sim = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
            ct.Send.println("教师 "+ sim);
            ct.Send.println("[警告]请务必集中注意力，认真听讲!");
            Chat.append("教师 "+ sim +"\n");
            Chat.append("[警告]请务必集中注意力，认真听讲!\n");
        }else{          //为绘图部分的按钮
            String name=e.getActionCommand();       //先获取触发事件命令名称
            switch(name){
                case"直线":
                case"圆形":
                case"矩形":
                case"铅笔":g2d.setStroke(new BasicStroke(3.0f));
                            nowButton=name; break;     //将当前的button设为命令名字
                case"画笔":g2d.setStroke(new BasicStroke(5.0f));   //设置画笔宽度
                            nowButton=name; break;
                case"清空":paintBoard.paint(g2d);sendEmpty();break;
                case"红":g2d.setColor(Color.red);
                        Now_color = "RED";sendColor("RED"); break;
                case"黄":g2d.setColor(Color.yellow);
                        Now_color = "YELLOW";sendColor("YELLOW"); break;
                case"蓝":g2d.setColor(Color.blue);
                        Now_color = "BLUE";sendColor("BLUE"); break;
                case"绿":g2d.setColor(Color.green);
                        Now_color = "GREEN";sendColor("GREEN"); break;
                case"黑":g2d.setColor(Color.black);
                        Now_color = "BLACK";sendColor("BLACK"); break;
                case"白":g2d.setColor(Color.white);
                        Now_color = "WHITE";sendColor("WHITE"); break;
            }
        }
    }

    //向所有学生发送绘制的图形信息。
    public void sendShape(){
        try {
            switch(nowButton){
                case "直线":
                    for(String ct : users_connect.keySet()){    //利用key值遍历哈希表
                        users_connect.get(ct).Send.println("LINE-"+shapePoint[0]
                                +"-"+shapePoint[1]+"-"+shapePoint[2]+"-"+shapePoint[3]);
                    }
                    break;
                case "圆形":
                    for(String ct : users_connect.keySet()){    //利用key值遍历哈希表
                        users_connect.get(ct).Send.println("YUAN-"+shapePoint[0]
                                +"-"+shapePoint[1]+"-"+shapePoint[2]+"-"+shapePoint[3]);
                    }
                    break;
                case "矩形":
                    for(String ct : users_connect.keySet()){    //利用key值遍历哈希表
                        users_connect.get(ct).Send.println("JUXING-"+shapePoint[0]
                                +"-"+shapePoint[1]+"-"+shapePoint[2]+"-"+shapePoint[3]);
                    }
                    break;
                case "铅笔":
                    for(String ct : users_connect.keySet()){    //利用key值遍历哈希表
                        users_connect.get(ct).Send.println("QIANBI-"+shapePoint[0]
                                +"-"+shapePoint[1]+"-"+shapePoint[2]+"-"+shapePoint[3]);
                    }
                    break;
                case "画笔":
                    for(String ct : users_connect.keySet()){    //利用key值遍历哈希表
                        users_connect.get(ct).Send.println("HUABI-"+shapePoint[0]
                                +"-"+shapePoint[1]+"-"+shapePoint[2]+"-"+shapePoint[3]);
                    }
            }
        } catch(Exception e) {}
    }

    //向所有学生发送当前选定的绘图颜色信息
    public void sendColor(String Color) {
        try {
            for(String ct : users_connect.keySet()){    //利用key值遍历哈希表
                users_connect.get(ct).Send.println("YANSE-"+Color);     //发送颜色的单词
            }
        } catch (Exception e) {}
    }

    //向所有学生发送清空画板的指令
    public void sendEmpty() {
        try {
            for(String ct : users_connect.keySet()){    //利用key值遍历哈希表
                users_connect.get(ct).Send.println("EMPTY");    //发送清空信号
            }
        } catch (Exception e) {}
    }

    //处理学生离开课堂时的操作。
    //发送学生退出的消息给所有在线学生，并从在线学生列表中移除该学生。
    public void Leave(String selectedUser){
        String msg = "LOGOUT-"+selectedUser;        //有学生离开课堂
        ChatThread ct = users_connect.get(selectedUser);
        ct.Send.println(msg);
        users.remove(selectedUser);
        users_connect.remove(selectedUser);
    }

    //实现了Runnable接口，用于监听学生端的连接请求。
    //不断地接受学生端的Socket连接，每个连接创建一个新的ChatThread线程处理学生端的消息和绘图操作。
    public void run(){
        while(true){
            try{
                Socket s = ss.accept();
                ChatThread ct = new ChatThread(s,this);
            }catch(Exception e){}
        }
    }

    //内部类，继承自Thread类，用于处理单个学生端的通信。
    //在构造函数中初始化学生端的输入输出流，并处理登录、注册、消息发送、绘图操作等功能。
    class ChatThread extends Thread{
        PrintStream Send = null;
        BufferedReader Read = null;
        String NickName = null;
        JFrame jFrame = null;
        ChatThread(Socket s,JFrame frame) throws Exception{
            Send = new PrintStream(s.getOutputStream());
            in = s.getInputStream();
            Read = new BufferedReader(new InputStreamReader(in));
            this.jFrame = frame;
            this.start();
        }
        public void run(){
            while(true){
                try{
                    String message = Read.readLine();
                    String[] msgs = message.split("-");
                    if(msgs[0].equals("REG1")){
                        if(msgs[1].equals(msgs[2])){
                            Send.println("YES");
                        }else{
                            Send.println("NO");
                        }
                    }else if(msgs[0].equals("REG2"))
                    {
                        try{
                            String sql = "select username from client where username=?";  //?为占位符
                            PreparedStatement ptmt = con.prepareStatement(sql);     //加入预编译语句
                            ptmt.setString(1,msgs[1]);  //1是ID
                            ResultSet rs = ptmt.executeQuery();
                            if(rs.next()){
                                Send.println("EXISTS");
                            }else{
                                Send.println("INSERT");
                                sql = "insert into client (username,password,picture_path) values(?,?,?)";  //?为占位符
                                ptmt = con.prepareStatement(sql);     //加入预编译语句
                                ptmt.setString(1,msgs[1]);
                                ptmt.setString(2,msgs[2]);
                                ptmt.setString(3,msgs[3]);
                                ptmt.execute();     //执行sql语句
                                ptmt.close();
                            }
                        }catch(Exception exce){}
                    }else if(msgs[0].equals("LOGIN")){
                        String sql= "select username,password,picture_path from client where username=? and password=?";
                        PreparedStatement ptmt = con.prepareStatement(sql);
                        ptmt.setString(1,msgs[1]);
                        ptmt.setString(2,msgs[2]);
                        ResultSet rs = ptmt.executeQuery();
                        if(rs.next()) {      //存在此人
                            String path = rs.getString(3);
                            for (String ct : users_connect.keySet()) {
                                if(msgs[1].equals(ct)){  //是否重复登录
                                    Send.println("CHONG");
                                    chongfu = false;
                                    break;
                                }
                            }
                            if(chongfu) {      //未重复
                                Send.println("OK-"+path);     //同意登录
                                NickName = msgs[1];
                                users.add(NickName);
                                users_connect.put(NickName, this);
                                serverFileThread = new ServerFileThread();  //服务器文件读写进程启动
                                serverFileThread.start();
                            }else{
                                chongfu = true;  //将重复标记重新设置为true
                            }
                        }else{      //拒绝登录
                            Send.println("NO");
                        }
                    }else if(msgs[0].equals("NEW")){
                        Calendar c = Calendar.getInstance();
                        String sim = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
                        for (String ct : users_connect.keySet()) {    //利用key值遍历哈希表
                            users_connect.get(ct).Send.println("系统消息 " + sim);
                            users_connect.get(ct).Send.println("SLOGIN-" + NickName);
                            if (!ct.equals(NickName)) {
                                Send.println("USER-" + ct);       //服务器发送之前的好友列表
                            }
                        }
                        new Thread() {      //等100ms再发颜色数据，以避免学生端g2d画笔还未初始化
                            public void run() {
                                try{
                                    Thread.sleep(100);
                                    Send.println("YANSE-"+Now_color);         //发送画笔颜色
                                }catch(Exception e){}
                            }
                        }.start();
                        Chat.append("系统消息 " + sim +"\n");
                        Chat.append(NickName+"进入了您的课堂。\n");
                    }else if(msgs[0].equals("RUN")){
                        String sim = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
                        for(String ct : users_connect.keySet()){    //利用key值遍历哈希表
                            users_connect.get(ct).Send.println("系统消息 "+sim);
                            users_connect.get(ct).Send.println("SLOGOUT-"+msgs[1]);
                        }
                        Chat.append("系统消息 " + sim +"\n");
                        Chat.append(NickName+"已经离开课堂。\n");
                    }else if(msgs[0].equals("LEAVE")){
                        Leave(NickName);
                    }else if(msgs[0].equals("RECORD")){
                        //有人要发语音
                        int result = JOptionPane.showConfirmDialog(jFrame, msgs[1]+"想要发言，是否同意？", "接收提醒",
                                JOptionPane.YES_NO_OPTION);
                        if(result == 0){
                            Send.println("OKRECORD");       //同意发言
                        }else{
                            Send.println("NORECORD");       //拒绝发言
                        }
                    }
                    else{   //普通消息发送
                        String sim = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
                        for(String ct : users_connect.keySet()){    //利用key值遍历哈希表
                            users_connect.get(ct).Send.println(msgs[0]+" "+ sim);
                            users_connect.get(ct).Send.println(msgs[1]);
                        }
                        Chat.append(msgs[0]+" "+ sim + "\n");
                        Chat.append(msgs[1]+"\n");
                    }
                }catch(Exception ex){}
            }
        }
    }

    public static void main(String[] args) throws Exception {
        new Teacher();
    }
}