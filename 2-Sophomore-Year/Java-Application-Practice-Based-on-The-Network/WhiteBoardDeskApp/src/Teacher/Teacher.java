/*
* ���ڽ�ʦ��ѧ��֮���Զ�̽�ѧ������Э�����ṩ�˶���ʵʱ�����ͽ�ѧ����֧��
*
* ��Ҫ���ܰ�����

    1 ������ƣ�ʹ��Swing�����ƽ�ʦ�˵��û����棬������ͼ�塢���ܰ�ť����ɫѡ������ѧ���б������¼��ʾ�ȡ�

    2 ���ݿ����ӣ�ͨ��JDBC����MySQL���ݿ⣬ʵ�ֽ�ʦ��ѧ���û��ĵ�¼��֤��ע�Ṧ�ܣ��������û���Ϣ��

    3 Socketͨ�ţ�ʹ��Socket��ServerSocketʵ�ֻ���TCP/IP��ͨ�ţ���ʦ��ͨ��ServerSocket�����˿ڣ�����ѧ���˵���������ʵ��ʵʱ����Ϣ���ݺͻ�ͼͬ�����ܡ�

    4 ����ʵ�֣�
        ��ͼ���ܣ�֧��ֱ�ߡ�Բ�Ρ����Ρ�Ǧ�ʡ����ʵȻ��ƹ��ߣ���ʦ���Ƶ�ͼ�ο���ʵʱͬ����ѧ���ˡ�
        ��Ϣ���ͣ���ʦ����Ⱥ����Ϣ����������ѧ��������������Ϣ���ļ����䡣
        ����ѧ������ʵʱ��ʾ��ǰ����ѧ���б���ʦ���Զ��ض�ѧ������������Ϣ��

    5 ���̴߳���ÿ��ѧ�����Ӷ�Ӧһ��ChatThread�̴߳���ͨ�ź���Ϣת����ȷ�����û�ͬʱ����ʱ�Ĳ�������������
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
    private static String url = "jdbc:mysql://localhost:3306/login?useSSL=false&allowPublicKeyRetrieval=true&serverTimezone=UTC";    //�������ݿ��url,login�����ݿ���
    private static String user = "";
    private static String pass = "";
    private static Connection con;

    private JLabel explain = new JLabel("����ѧ��",JLabel.CENTER);
    private List users = new List();
    private JButton Send_Button = new JButton("������Ϣ");
    private JButton Send_File = new JButton("�����ļ�");
    private JButton Send_Remind = new JButton("��������");
    private JTextField Sendword = new JTextField(20);       //����������
    private JTextArea Chat = new JTextArea(10,45);     //�����¼��ʾ
    private ServerSocket ss = null;
    private Font font = new Font("΢���ź�", Font.PLAIN, 14);
    private HashMap<String,ChatThread> users_connect = new HashMap<String,ChatThread>();
    private JPanel paintBoard = new JPanel();   //��ͼ��
    private JPanel buttonBoard=new JPanel();    //��ť���
    private JPanel jpRight=new JPanel();        //�滭���
    private JLabel exp1 = new JLabel("�װ��������",JLabel.CENTER);
    private JLabel exp2 = new JLabel("RuShawn 24-6",JLabel.CENTER);
    private boolean chongfu = true;
    private String Record_path = null;
    private InputStream in = null;
    private ServerFileThread serverFileThread = null;
    private int[] shapePoint=new int[4];        //���û���ͼ�ε��ĸ���
    private Graphics2D g2d;                  //Graphics2D���͵Ļ���
    private String nowButton = "Ǧ��";       //���ڼ�¼��ǰʹ�õ����ĸ���ť���ڻ����Ͻ�����Ӧ������Ĭ��ΪǦ��
    private String Now_color = "BLACK";     //����Ĭ��ֵΪ��ɫ���ñ������ں���ѧ���������ʱ�������ʦ������ɫ

    //��ʼ��������ʦ��Ӧ�ó���Ľ���͸������
    public Teacher() throws Exception{
        this.setLayout(null);
        Class.forName("com.mysql.cj.jdbc.Driver");  //Class.forName�����Ҳ�����ָ������,�������ݿ���������������
        con = DriverManager.getConnection(url,user,pass);
        paintBoard.setBounds(500,0,598,598);
        paintBoard.setBackground(Color.white);  //������ɫ
        paintBoard.addMouseListener(this);
        paintBoard.addMouseMotionListener(this);
        buttonBoard.setBounds(1100,90,85,120);
        buttonBoard.setLayout(new GridLayout(6,1));  //����Ϊ���񲼾�
        //��ӹ��ܰ�ť
        String[] buttonNames={"ֱ��","Բ��","����","Ǧ��","����","���"};
        JButton[] jbtList=new JButton[buttonNames.length];
        for(int i=0;i<buttonNames.length;i++){
            jbtList[i]=new JButton(buttonNames[i]);
            jbtList[i].setFont(new Font("΢���ź�", Font.PLAIN, 12));
            jbtList[i].setActionCommand(buttonNames[i]);    //����ͼ�괥���Ĳ����¼�����������
            jbtList[i].addActionListener(this);           //��Ӽ���
            buttonBoard.add(jbtList[i]);
        }
        jpRight.setBounds(1100,210,85,75);     //��ͼ���
        jpRight.setLayout(new GridLayout(3,2));        //����Ϊ���񲼾�
        //�����ɫ��ť
        Color[] colors={Color.red,Color.yellow,Color.blue,Color.green,Color.black,Color.white};
        String[] colorButtonNames={"��","��","��","��","��","��"};
        JButton[] CjbtList=new JButton[colorButtonNames.length];
        for(int i=0;i<colorButtonNames.length;i++){
            CjbtList[i]=new JButton();
            CjbtList[i].setActionCommand(colorButtonNames[i]);
            CjbtList[i].setBackground(colors[i]);
            CjbtList[i].addActionListener(this);     //��Ӽ���
            jpRight.add(CjbtList[i]);
        }
        //����Ϊ�����ؼ�����
        explain.setSize(100,20);       //����ѧ���ĸ���
        explain.setLocation(1093,285);
        explain.setFont(new Font("΢���ź�", Font.BOLD, 15));
        users.setSize(86,200);
        users.setLocation(1099,305);
        users.setFont(new Font("Consolas", Font.PLAIN, 15));
        Sendword.addActionListener(this);
        Sendword.setLocation(0,500);
        Sendword.setSize(300,60);
        Sendword.setFont(new Font("΢���ź�", Font.PLAIN, 20));
        Send_Button.addActionListener(this);
        Send_Button.setSize(67,60);
        Send_Button.setLocation(300,500);
        Send_Button.setFont(new Font("΢���ź�", Font.PLAIN, 14));
        Send_Button.setMargin(new Insets(0,0,0,0));   //���ð�ť�߿�ͱ�ǩ֮��հ�Ϊ0
        Send_File.addActionListener(this);
        Send_File.setSize(67,60);
        Send_File.setLocation(367,500);
        Send_File.setFont(font);
        Send_File.setMargin(new Insets(0,0,0,0));   //���ð�ť�߿�ͱ�ǩ֮��հ�Ϊ0
        Send_Remind.addActionListener(this);
        Send_Remind.setSize(66,60);
        Send_Remind.setLocation(434,500);
        Send_Remind.setFont(font);
        Send_Remind.setMargin(new Insets(0,0,0,0));   //���ð�ť�߿�ͱ�ǩ֮��հ�Ϊ0
        Chat.setFont(new Font("΢���ź�", Font.PLAIN, 15));
        Chat.setLineWrap(true);         //�����Զ�����
        Chat.setLocation(0,0);
        Chat.setEditable(false);        //�����¼�޷��༭
        Chat.setMargin(new Insets(7, 7, 7, 7));     //����7mm�߾�
        JScrollPane jsp = new JScrollPane(Chat);         //����һ��������
        jsp.setBounds(0,0,500,500);
        ImageIcon image = new ImageIcon("");  //��ͼƬ·����Ϊ��������
        image.setImage(image.getImage().getScaledInstance(85,90,Image.SCALE_DEFAULT));  //�������Ű汾ͼ��
        JLabel Picture = new JLabel(image);
        Picture.setLocation(1100,0);
        Picture.setSize(85,90);
        exp1.setSize(100,20);     //�����б��ĸ���
        exp1.setLocation(1093,510);
        exp1.setFont(new Font("΢���ź�", Font.BOLD, 11));
        exp2.setSize(100,20);     //�����б��ĸ���
        exp2.setLocation(1093,530);
        exp2.setFont(new Font("΢���ź�", Font.BOLD, 11));
        this.setTitle("��ʦ��");
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
        Graphics g = paintBoard.getGraphics();         //��ȡ����
        g2d=(Graphics2D) g;      //��GraphicsתΪGraphics2D
        g2d.setStroke(new BasicStroke(3.0f));   //���û��ʿ��
        //����ServerSocket������ѧ���˵��������󣬲��������̴߳���ÿ��ѧ����ͨ��
        ss = new ServerSocket(10222);    //��Ϣ����ʹ�ö˿�
        new Thread(this).start();
    }

    //MouseListener�еķ�����ʵ����MouseListener�ӿڣ����ڼ�¼��갴��ʱ�����꣬���ڻ�ͼ�����е���״������ʼ���¼��
    public void mousePressed(MouseEvent e) {
        //��¼��갴�µ�����
        shapePoint[0]=e.getX();
        shapePoint[1]=e.getY();
    }

    //ʵ����MouseListener�ӿڣ����ڼ�¼����ͷ�ʱ�����꣬���ڻ�ͼ�����е���״���ƽ������¼�������ݵ�ǰѡ��Ļ�ͼ���߻��ƶ�Ӧ��ͼ�Ρ�
    public void mouseReleased(MouseEvent e) {
        //��¼����ɿ�������
        shapePoint[2]=e.getX();
        shapePoint[3]=e.getY();
        //�ж�����µ����ĸ�ͼ�ΰ�ť
        switch(nowButton){
            case "ֱ��":
                //����ֱ��
                g2d.drawLine(shapePoint[0],shapePoint[1],shapePoint[2],shapePoint[3]);
                //���÷���ͼ�η���
                sendShape();
                break;
            case "Բ��":
                //��¼Բ�����Ͻ�����㣬����������
                int x1=Math.min(shapePoint[0],shapePoint[2]);
                int y1=Math.min(shapePoint[1],shapePoint[3]);
                int width=Math.abs(shapePoint[0]-shapePoint[2]);
                int height=Math.abs(shapePoint[1]-shapePoint[3]);
                shapePoint[0]=x1;
                shapePoint[1]=y1;
                shapePoint[2]=width;
                shapePoint[3]=height;
                //������Բ
                g2d.fillOval(shapePoint[0],shapePoint[1],shapePoint[2],shapePoint[3]);
                //���÷���ͼ�η���
                sendShape();
                break;
            case "����":
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

    //����Ǧ�ʵķ�����ʵ����MouseMotionListener�ӿڣ����ڴ�������϶��¼�����Ҫ����Ǧ�ʺͻ��ʹ����е��������Ʋ�����
    public void mouseDragged(MouseEvent e) {
        if(nowButton.equals("Ǧ��") || nowButton.equals("����")){
            shapePoint[2]=shapePoint[0];
            shapePoint[3]=shapePoint[1];

            shapePoint[0]=e.getX();
            shapePoint[1]=e.getY();

            g2d.drawLine(shapePoint[0],shapePoint[1],shapePoint[2],shapePoint[3]);

            sendShape();
        }
    }

    //���¾�Ϊ��д����
    public void mouseMoved(MouseEvent e) {}
    public void mouseClicked(MouseEvent e) {}
    public void mouseEntered(MouseEvent e) {}
    public void mouseExited(MouseEvent e) {}

    //ʵ����ActionListener�ӿڣ������û������и�����ť�ĵ���¼�
    public void actionPerformed(ActionEvent e){
        if(e.getSource() == Sendword || e.getSource() == Send_Button){
            //Ⱥ����Ϣ��ť
            for(String ct : users_connect.keySet()){    //����keyֵ������ϣ��
                users_connect.get(ct).Send.println("��ʦ "+new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date()));
                users_connect.get(ct).Send.println(Sendword.getText());
            }
            String sim = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
            Chat.append("��ʦ "+ sim +"\n");
            Chat.append(Sendword.getText()+"\n");
            Sendword.setText("");       //��������
        }else if(e.getSource() == Send_File){
            FileDialog fLoader = new FileDialog(this,"ѡ��򿪵��ļ�",FileDialog.LOAD);
            fLoader.setVisible(true);
            String path = fLoader.getDirectory() + fLoader.getFile();
            FileReadAndWrite.outFileToClient(path);    //���ļ��ַ���ѧ����
            //Ⱥ����Ϣ��ť
            for(String ct : users_connect.keySet()){    //����keyֵ������ϣ��
                users_connect.get(ct).Send.println("��ʦ "+new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date()));
                users_connect.get(ct).Send.println("[�ļ���������]������һ���ļ���");
            }
            String sim = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
            Chat.append("��ʦ "+ sim +"\n");
            Chat.append("[�ļ���������]������һ���ļ���\n");
        }else if(e.getSource() == Send_Remind){
            //������������
            String selectedUser = users.getSelectedItem();
            String msg = "CARE";
            ChatThread ct = users_connect.get(selectedUser);
            ct.Send.println(msg);       //CARE����
            String sim = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
            ct.Send.println("��ʦ "+ sim);
            ct.Send.println("[����]����ؼ���ע��������������!");
            Chat.append("��ʦ "+ sim +"\n");
            Chat.append("[����]����ؼ���ע��������������!\n");
        }else{          //Ϊ��ͼ���ֵİ�ť
            String name=e.getActionCommand();       //�Ȼ�ȡ�����¼���������
            switch(name){
                case"ֱ��":
                case"Բ��":
                case"����":
                case"Ǧ��":g2d.setStroke(new BasicStroke(3.0f));
                            nowButton=name; break;     //����ǰ��button��Ϊ��������
                case"����":g2d.setStroke(new BasicStroke(5.0f));   //���û��ʿ��
                            nowButton=name; break;
                case"���":paintBoard.paint(g2d);sendEmpty();break;
                case"��":g2d.setColor(Color.red);
                        Now_color = "RED";sendColor("RED"); break;
                case"��":g2d.setColor(Color.yellow);
                        Now_color = "YELLOW";sendColor("YELLOW"); break;
                case"��":g2d.setColor(Color.blue);
                        Now_color = "BLUE";sendColor("BLUE"); break;
                case"��":g2d.setColor(Color.green);
                        Now_color = "GREEN";sendColor("GREEN"); break;
                case"��":g2d.setColor(Color.black);
                        Now_color = "BLACK";sendColor("BLACK"); break;
                case"��":g2d.setColor(Color.white);
                        Now_color = "WHITE";sendColor("WHITE"); break;
            }
        }
    }

    //������ѧ�����ͻ��Ƶ�ͼ����Ϣ��
    public void sendShape(){
        try {
            switch(nowButton){
                case "ֱ��":
                    for(String ct : users_connect.keySet()){    //����keyֵ������ϣ��
                        users_connect.get(ct).Send.println("LINE-"+shapePoint[0]
                                +"-"+shapePoint[1]+"-"+shapePoint[2]+"-"+shapePoint[3]);
                    }
                    break;
                case "Բ��":
                    for(String ct : users_connect.keySet()){    //����keyֵ������ϣ��
                        users_connect.get(ct).Send.println("YUAN-"+shapePoint[0]
                                +"-"+shapePoint[1]+"-"+shapePoint[2]+"-"+shapePoint[3]);
                    }
                    break;
                case "����":
                    for(String ct : users_connect.keySet()){    //����keyֵ������ϣ��
                        users_connect.get(ct).Send.println("JUXING-"+shapePoint[0]
                                +"-"+shapePoint[1]+"-"+shapePoint[2]+"-"+shapePoint[3]);
                    }
                    break;
                case "Ǧ��":
                    for(String ct : users_connect.keySet()){    //����keyֵ������ϣ��
                        users_connect.get(ct).Send.println("QIANBI-"+shapePoint[0]
                                +"-"+shapePoint[1]+"-"+shapePoint[2]+"-"+shapePoint[3]);
                    }
                    break;
                case "����":
                    for(String ct : users_connect.keySet()){    //����keyֵ������ϣ��
                        users_connect.get(ct).Send.println("HUABI-"+shapePoint[0]
                                +"-"+shapePoint[1]+"-"+shapePoint[2]+"-"+shapePoint[3]);
                    }
            }
        } catch(Exception e) {}
    }

    //������ѧ�����͵�ǰѡ���Ļ�ͼ��ɫ��Ϣ
    public void sendColor(String Color) {
        try {
            for(String ct : users_connect.keySet()){    //����keyֵ������ϣ��
                users_connect.get(ct).Send.println("YANSE-"+Color);     //������ɫ�ĵ���
            }
        } catch (Exception e) {}
    }

    //������ѧ��������ջ����ָ��
    public void sendEmpty() {
        try {
            for(String ct : users_connect.keySet()){    //����keyֵ������ϣ��
                users_connect.get(ct).Send.println("EMPTY");    //��������ź�
            }
        } catch (Exception e) {}
    }

    //����ѧ���뿪����ʱ�Ĳ�����
    //����ѧ���˳�����Ϣ����������ѧ������������ѧ���б����Ƴ���ѧ����
    public void Leave(String selectedUser){
        String msg = "LOGOUT-"+selectedUser;        //��ѧ���뿪����
        ChatThread ct = users_connect.get(selectedUser);
        ct.Send.println(msg);
        users.remove(selectedUser);
        users_connect.remove(selectedUser);
    }

    //ʵ����Runnable�ӿڣ����ڼ���ѧ���˵���������
    //���ϵؽ���ѧ���˵�Socket���ӣ�ÿ�����Ӵ���һ���µ�ChatThread�̴߳���ѧ���˵���Ϣ�ͻ�ͼ������
    public void run(){
        while(true){
            try{
                Socket s = ss.accept();
                ChatThread ct = new ChatThread(s,this);
            }catch(Exception e){}
        }
    }

    //�ڲ��࣬�̳���Thread�࣬���ڴ�����ѧ���˵�ͨ�š�
    //�ڹ��캯���г�ʼ��ѧ���˵�������������������¼��ע�ᡢ��Ϣ���͡���ͼ�����ȹ��ܡ�
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
                            String sql = "select username from client where username=?";  //?Ϊռλ��
                            PreparedStatement ptmt = con.prepareStatement(sql);     //����Ԥ�������
                            ptmt.setString(1,msgs[1]);  //1��ID
                            ResultSet rs = ptmt.executeQuery();
                            if(rs.next()){
                                Send.println("EXISTS");
                            }else{
                                Send.println("INSERT");
                                sql = "insert into client (username,password,picture_path) values(?,?,?)";  //?Ϊռλ��
                                ptmt = con.prepareStatement(sql);     //����Ԥ�������
                                ptmt.setString(1,msgs[1]);
                                ptmt.setString(2,msgs[2]);
                                ptmt.setString(3,msgs[3]);
                                ptmt.execute();     //ִ��sql���
                                ptmt.close();
                            }
                        }catch(Exception exce){}
                    }else if(msgs[0].equals("LOGIN")){
                        String sql= "select username,password,picture_path from client where username=? and password=?";
                        PreparedStatement ptmt = con.prepareStatement(sql);
                        ptmt.setString(1,msgs[1]);
                        ptmt.setString(2,msgs[2]);
                        ResultSet rs = ptmt.executeQuery();
                        if(rs.next()) {      //���ڴ���
                            String path = rs.getString(3);
                            for (String ct : users_connect.keySet()) {
                                if(msgs[1].equals(ct)){  //�Ƿ��ظ���¼
                                    Send.println("CHONG");
                                    chongfu = false;
                                    break;
                                }
                            }
                            if(chongfu) {      //δ�ظ�
                                Send.println("OK-"+path);     //ͬ���¼
                                NickName = msgs[1];
                                users.add(NickName);
                                users_connect.put(NickName, this);
                                serverFileThread = new ServerFileThread();  //�������ļ���д��������
                                serverFileThread.start();
                            }else{
                                chongfu = true;  //���ظ������������Ϊtrue
                            }
                        }else{      //�ܾ���¼
                            Send.println("NO");
                        }
                    }else if(msgs[0].equals("NEW")){
                        Calendar c = Calendar.getInstance();
                        String sim = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
                        for (String ct : users_connect.keySet()) {    //����keyֵ������ϣ��
                            users_connect.get(ct).Send.println("ϵͳ��Ϣ " + sim);
                            users_connect.get(ct).Send.println("SLOGIN-" + NickName);
                            if (!ct.equals(NickName)) {
                                Send.println("USER-" + ct);       //����������֮ǰ�ĺ����б�
                            }
                        }
                        new Thread() {      //��100ms�ٷ���ɫ���ݣ��Ա���ѧ����g2d���ʻ�δ��ʼ��
                            public void run() {
                                try{
                                    Thread.sleep(100);
                                    Send.println("YANSE-"+Now_color);         //���ͻ�����ɫ
                                }catch(Exception e){}
                            }
                        }.start();
                        Chat.append("ϵͳ��Ϣ " + sim +"\n");
                        Chat.append(NickName+"���������Ŀ��á�\n");
                    }else if(msgs[0].equals("RUN")){
                        String sim = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
                        for(String ct : users_connect.keySet()){    //����keyֵ������ϣ��
                            users_connect.get(ct).Send.println("ϵͳ��Ϣ "+sim);
                            users_connect.get(ct).Send.println("SLOGOUT-"+msgs[1]);
                        }
                        Chat.append("ϵͳ��Ϣ " + sim +"\n");
                        Chat.append(NickName+"�Ѿ��뿪���á�\n");
                    }else if(msgs[0].equals("LEAVE")){
                        Leave(NickName);
                    }else if(msgs[0].equals("RECORD")){
                        //����Ҫ������
                        int result = JOptionPane.showConfirmDialog(jFrame, msgs[1]+"��Ҫ���ԣ��Ƿ�ͬ�⣿", "��������",
                                JOptionPane.YES_NO_OPTION);
                        if(result == 0){
                            Send.println("OKRECORD");       //ͬ�ⷢ��
                        }else{
                            Send.println("NORECORD");       //�ܾ�����
                        }
                    }
                    else{   //��ͨ��Ϣ����
                        String sim = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date());
                        for(String ct : users_connect.keySet()){    //����keyֵ������ϣ��
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