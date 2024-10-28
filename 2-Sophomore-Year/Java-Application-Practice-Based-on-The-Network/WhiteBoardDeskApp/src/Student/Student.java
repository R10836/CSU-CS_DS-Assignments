/*
* ��Ҫ����ѧ���˵�ͼ���û��������������Ľ���
* */

package Student;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.*;

// Student��
public class Student extends JFrame implements ActionListener,Runnable, MouseListener {
	private String NickName = null;

	//GUI�����������ʾ�Ϳ��ƽ���Ԫ�ء�
	private JScrollPane jsp = new JScrollPane();
	private JButton Send = new JButton("������Ϣ");
	private JButton Send_Record = new JButton("���ַ���");
	private JButton Leave = new JButton("�뿪����");

	private DefaultListModel<String> user = new DefaultListModel<String>();  //�û��б�
	private JList<String> userList = new JList<String>(user);   //չʾ�û��б�

	private JScrollPane listPane = new JScrollPane(userList);       //���ù�����ͼ

	private JTextField Sendword = new JTextField(20);       //����������
	private JTextArea Chat = new JTextArea(10,45);     //�����¼��ʾ

	//��ǩ��������ʾѧ����Ϣ�������ı���
	private JLabel myself = new JLabel("",JLabel.CENTER);
	private JLabel friend_list = new JLabel("����ѧ��",JLabel.CENTER);
	private JLabel exp1 = new JLabel("",JLabel.CENTER);
	private JLabel exp2 = new JLabel("",JLabel.CENTER);

	private JPanel paintBoard = new JPanel();   //��ͼ�壬���ڻ���ͼ��

	//�����������ͨ�ŵ������������
	public PrintStream ps = null;
	public BufferedReader br = null;

	private String path;
	private int[] shapePoint=new int[4];  //����ͼ�ε��ĸ���
	private Graphics2D g2d;  //Graphics2D���͵Ļ���
	private OutputStream out;
	private RecordMain re = null;

	//��ʼ��
	public Student(String Nick, String path, PrintStream ps, BufferedReader br, OutputStream out) throws Exception{
		this.ps = ps;
		this.br = br;
		this.path = path;
		this.out = out;
		ps.println("NEW");
		Font font = new Font("΢���ź�", Font.PLAIN, 15);
		paintBoard.setBounds(500,0,598,598);
		paintBoard.setBackground(Color.white);      //����Ϊ�װ�
		Chat.setFont(font);
		Chat.setLineWrap(true);         //�����Զ�����
		Chat.setLocation(0,0);
		Chat.setEditable(false);        //�����¼�޷��༭
		Chat.setMargin(new Insets(7, 7, 7, 7));     //����7mm�߾�
		JScrollPane jsp = new JScrollPane(Chat);         //����һ��������
		jsp.setBounds(0,0,500,500);
		//���ÿؼ�λ��
		Sendword.setLocation(0,500);
		Sendword.setSize(300,60);
		Sendword.setFont(new Font("΢���ź�", Font.PLAIN, 20));
		Sendword.addActionListener(this);
		Send.addActionListener(this);
		Send.setSize(100,60);
		Send.setLocation(300,500);
		Send.setFont(font);
		Send.setMargin(new Insets(0,0,0,0));   //���ð�ť�߿�ͱ�ǩ֮��հ�Ϊ0
		Send_Record.addActionListener(this);
		Send_Record.setSize(100,60);
		Send_Record.setLocation(400,500);
		Send_Record.setFont(font);
		Send_Record.setMargin(new Insets(0,0,0,0));   //���ð�ť�߿�ͱ�ǩ֮��հ�Ϊ0
		Leave.addActionListener(this);
		Leave.setSize(85,69);
		Leave.setLocation(1099,429);
		Leave.setFont(font);
		Leave.setMargin(new Insets(0,0,0,0));   //���ð�ť�߿�ͱ�ǩ֮��հ�Ϊ0
		Leave.setBackground(new Color(255,255,204));          //���ð�ť��ɫΪ����
		exp1.setSize(100,20);     //�����б��ĸ���
		exp1.setLocation(1093,510);
		exp1.setFont(new Font("΢���ź�", Font.BOLD, 11));
		exp2.setSize(100,20);     //�����б��ĸ���
		exp2.setLocation(1093,530);
		exp2.setFont(new Font("΢���ź�", Font.BOLD, 11));
		listPane.setSize(86,289);
		listPane.setLocation(1099,140);
		userList.setFont(font);
		userList.addMouseListener(this);    //���ڼ���˽��
		ImageIcon image = new ImageIcon(path);  //��ͼƬ·����Ϊ��������
		image.setImage(image.getImage().getScaledInstance(85,90,Image.SCALE_DEFAULT));  //�������Ű汾ͼ��
		JLabel Picture = new JLabel(image);
		Picture.setLocation(1100,0);
		Picture.setSize(85,90);
		this.NickName = Nick;        //���캯���������
		myself.setText(NickName);
		myself.setSize(100,20);
		myself.setLocation(1093,95);
		myself.setFont(new Font("΢���ź�", Font.BOLD, 15));
		friend_list.setSize(100,20);     //�����б��ĸ���
		friend_list.setLocation(1093,118);
		friend_list.setFont(new Font("΢���ź�", Font.BOLD, 15));
		new Thread(this).start();
		//�ͻ����ļ���д�߳�����,���Լ�JFrame��Ϊ�������롣�����µ��߳����ڼ�����������Ϣ��
		ClientFileThread fileThread = new ClientFileThread(NickName,this,ps);
		fileThread.start();
		//�����������
		this.setLayout(null);
		this.add(paintBoard);
		this.add(jsp);
		this.add(exp1);
		this.add(exp2);
		this.add(Sendword);
		this.add(Send);
		this.add(Send_Record);
		this.add(listPane);
		this.add(Picture);
		this.add(myself);
		this.add(friend_list);
		this.add(Leave);
		this.setTitle(NickName+"�Ŀ���");
		this.setLocation(200,100);
		this.setSize(1200,598);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		this.setVisible(true);
		Graphics g = paintBoard.getGraphics();         //��ȡ����
		g2d=(Graphics2D) g;      //��GraphicsתΪGraphics2D
		g2d.setStroke(new BasicStroke(3.0f));   //���û��ʿ��
	}

	// �������������͵���Ϣ����������Ϣ���ݽ��в�ͬ�Ĵ���������û��б���ʾ������Ϣ������ͼ�ε�
	public void run(){
		while(true){
			try{
				String message = br.readLine();
				String[] msgs = message.split("-");
				if(msgs[0].equals("LOGOUT")){
					ps.println("RUN-"+NickName);        //ʹ�������ܹ��ñ���֪����Ϣ
					JOptionPane.showMessageDialog(this, "�����뿪���ã��ټ���");
					this.dispose();
				}else if(msgs[0].equals("SLOGIN")){
					Chat.append("��ӭ"+msgs[1]+"�������!\n");
					if(!msgs[1].equals(NickName)){
						user.addElement(msgs[1]);       //���û���������б�
					}
					userList.repaint();
				} else if(msgs[0].equals("USER")){
					user.addElement(msgs[1]);           //������Ϊ�ͻ��˷���֮ǰ�ĺ����б�
				} else if(msgs[0].equals("SLOGOUT")){
					user.removeElement(msgs[1]);    //���û��Ƴ������б�
					userList.repaint();
				} else if(msgs[0].equals("CARE")){
					JFrame jf = this;				//������ڵĽ���
					new Thread() {      //�������ڶ����߳�
						long begin = System.currentTimeMillis();
						long end = System.currentTimeMillis();
						Point p = jf.getLocationOnScreen();
						public void run() {
							int i = 1;
							while ((end - begin) / 1000 < 2) {
								jf.setLocation(new Point((int) p.getX() - 5 * i, (int) p.getY() + 5 * i));  //Point�������첢��ʼ����
								end = System.currentTimeMillis();
								try {
									Thread.sleep(5);
									i = -i;
									jf.setLocation(p);
								} catch (InterruptedException e) {
									e.printStackTrace();
								}
							}
						}
					}.start();
				}else if(msgs[0].equals("OKRECORD")){
					re = new RecordMain();           //����¼�ƽ���
					re.setLocationRelativeTo(this);  //�����ڱ�ҳ���м�
					WaitingThread waiting = new WaitingThread();
					waiting.start();
				}else if(msgs[0].equals("NORECORD")){
					JOptionPane.showMessageDialog(this,"��ʦ�ܾ������ķ�������");
				}else if(msgs[0].equals("LINE") ||msgs[0].equals("YUAN")||
						msgs[0].equals("JUXING")||msgs[0].equals("QIANBI")||msgs[0].equals("HUABI")) {
					//�ı仭�ʵĴ�ϸ
					if(msgs[0].equals("QIANBI")){
						g2d.setStroke(new BasicStroke(3.0f));
					}else if(msgs[0].equals("HUABI")){
						g2d.setStroke(new BasicStroke(5.0f));
					}
					//��������+�ĸ���
					readShape(msgs[0],Integer.parseInt(msgs[1]),Integer.parseInt(msgs[2]),
							Integer.parseInt(msgs[3]),Integer.parseInt(msgs[4]));
				}else if(msgs[0].equals("EMPTY")){
					paintBoard.paint(g2d);			//�������
				}else if(msgs[0].equals("YANSE")){
					changeColor(msgs[1]);			//msgs[1]Ϊ��ɫӢ�ﵥ��
				}else{
					Chat.append(message+"\n");
				}
			}catch(Exception e){}
		}
	}

	// ����ť����¼����緢����Ϣ�������ԡ��뿪���õȡ�
	public void actionPerformed(ActionEvent e){
		if(e.getSource() == Send || e.getSource() == Sendword) {
			ps.println(NickName + "-" + Sendword.getText());
			Sendword.setText("");               //����ı���
		}
		else if(e.getSource() == Send_Record){
			ps.println("RECORD-"+NickName);
		}else if(e.getSource() == Leave){      //Ҫ����
			ps.println("LEAVE");
		}
	}

	//�������˫���¼�������˽�Ĺ��ܡ�
	public void mouseClicked(MouseEvent e) {
		if(e.getClickCount() == 2) {        //����˫���¼�
			ps.println("SILIAO" + "-" + userList.getSelectedValue());       //�������������˽����Ϣ
		}
	}

	//���¾�Ϊ��д����
	public void mouseEntered(MouseEvent e) {}
	public void mouseExited(MouseEvent e) {}
	public void mousePressed(MouseEvent e) {}
	public void mouseReleased(MouseEvent e) {}

	//���ݲ������ͻ���ͼ�Σ���������Բ�Ρ����ε�
	public void readShape(String OP,int point1,int point2,int point3,int point4){
		//ֻҪ�Ǵ����������ͼ�λ��Ʋ�������������һ��
		try {
			switch(OP){
				case "LINE":
				case "QIANBI":
				case "HUABI":
					g2d.drawLine(point1,point2,point3,point4);break;
				case "YUAN":
					g2d.fillOval(point1,point2,point3,point4);break;
				case "JUXING":
					g2d.fillRect(point1,point2,point3,point4);break;
			}
		} catch (Exception e) {}
	}

	//�ı仭����ɫ
	public void changeColor(String color){
		try {
			switch(color){
				case "RED": g2d.setColor(Color.red);break;
				case "YELLOW":
					g2d.setColor(Color.yellow);break;
				case "BLUE": g2d.setColor(Color.blue);break;
				case "GREEN":g2d.setColor(Color.green); break;
				case "BLACK":g2d.setColor(Color.black); break;
				case "WHITE":g2d.setColor(Color.white); break;
			}
		} catch (Exception e) {}
	}

	//�ȴ�¼����ɲ�����¼���ļ�����������
	class WaitingThread extends Thread{
		public void run(){
			while(true){
				try{
					Thread.sleep(50);
				}catch(Exception e){}
				if(RecordMain.flag){
					//�Ѿ�¼�꣬���øú��������ļ���������
					ClientFileThread.outFileToServer(MyRecorder.path);
					RecordMain.flag = false;    //��ֵ��Ϊfalse��������һ�η�����
					break;
				}
			}
		}
	}
}