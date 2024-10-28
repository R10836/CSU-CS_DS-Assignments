/*
* ʵ����һ���û�ע����棬��Ҫ���ܰ����û��˺�ע�ᡢ������֤��
*
*
* */

package Student;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.PrintStream;
import java.sql.Connection;

//
class Register extends JFrame implements ActionListener {
    private JTextField Id = new JTextField(20);  //���������˺ŵ��ı��ֶ�
    //�������������ȷ������������ֶΡ�
    private JPasswordField Passwd =new JPasswordField(20);
    private JPasswordField querenPasswd =new JPasswordField(20);
    private static Connection con;              //��������
    //��ǩ��������ʾ��ʾ��Ϣ��
    private JLabel welcome = new JLabel("",JLabel.CENTER);
    private JLabel zhanghao = new JLabel("�˺�:");
    private JLabel mima = new JLabel("����:");
    private JLabel querenmima = new JLabel("ȷ������:");
    private JLabel tip = new JLabel("ͷ��");
    private JButton Zhuce_Button = new JButton("ע��");
    private JButton Pic_acquire = new JButton();
    private FileDialog dialog = null;
    private String path = "";
    //�����������ͨ�ŵ����������
    public PrintStream ps = null;
    public BufferedReader br = null;

    //��ʼ��
    public Register(PrintStream ps, BufferedReader br) throws Exception{
        this.ps = ps;
        this.br = br;
        this.setLayout(null);
        Font font = new Font("΢���ź�", Font.PLAIN, 25);
        welcome.setLocation(20,50);
        welcome.setSize(600,80);
        welcome.setFont(new Font("΢���ź�", Font.BOLD, 45));
        Id.setLocation(290,200);
        Id.setSize(300,50);
        Id.setFont(font);
        Passwd.setLocation(290,260);
        Passwd.setSize(300,50);
        Passwd.setFont(font);
        querenPasswd.setLocation(290,320);
        querenPasswd.setSize(300,50);
        querenPasswd.setFont(font);
        zhanghao.setLocation(180,190);
        zhanghao.setSize(200,60);
        zhanghao.setFont(new Font("΢���ź�", Font.BOLD, 25));
        mima.setLocation(180,250);
        mima.setSize(200,60);
        mima.setFont(new Font("΢���ź�", Font.BOLD, 25));
        querenmima.setLocation(180,310);
        querenmima.setSize(200,60);
        querenmima.setFont(new Font("΢���ź�", Font.BOLD, 25));
        ImageIcon image = new ImageIcon("");  //��ͼƬ·����Ϊ��������
        image.setImage(image.getImage().getScaledInstance(100,100,Image.SCALE_DEFAULT));  //�������Ű汾ͼ��
        Pic_acquire.setIcon(image);
        Pic_acquire.setLocation(60, 230);
        Pic_acquire.setSize(100,100);
        Pic_acquire.setFont(font);
        Pic_acquire.addActionListener(this);
        tip.setLocation(75,310);
        tip.setSize(200,80);
        tip.setFont(new Font("΢���ź�", Font.PLAIN, 15));
        Zhuce_Button.setLocation(200, 400);
        Zhuce_Button.setSize(200,60);
        Zhuce_Button.setFont(font);
        Zhuce_Button.addActionListener(this);
        //�����������
        this.add(welcome);
        this.add(Id);
        this.add(Passwd);
        this.add(querenPasswd);
        this.add(zhanghao);
        this.add(mima);
        this.add(querenmima);
        this.add(Zhuce_Button);
        this.add(Pic_acquire);
        this.add(tip);
        this.setTitle("��ӭע��");
        this.setLocation(200,100);
        this.setSize(620,550);
        this.setVisible(true);
    }

    // ����ť����¼�
    public void actionPerformed(ActionEvent e) {
        if(e.getSource() == Pic_acquire) {       //��ȡͷ��
            dialog = new FileDialog(this, "ѡ����Ҫ���ص�ͼƬ", FileDialog.LOAD);
            dialog.setVisible(true);
            path = dialog.getDirectory() + dialog.getFile();
            ImageIcon image = new ImageIcon(path);  //��ͼƬ·����Ϊ��������
            image.setImage(image.getImage().getScaledInstance(85, 90, Image.SCALE_DEFAULT));  //�������Ű汾ͼ��
            JLabel Picture = new JLabel(image);
            Picture.setLocation(60, 230);
            Picture.setSize(100, 100);
            this.add(Picture);      //��ͼƬ�������
            Pic_acquire.setVisible(false);
            tip.setVisible(false);
        }
        else {      //ע��
            try{
                String passwd1 = String.valueOf(Passwd.getPassword());  //getPassword�õ������ַ����飬ҪתΪ�ַ�������
                String passwd2 = String.valueOf(querenPasswd.getPassword());
                if(Id.getText().isEmpty()||passwd1.isEmpty()||passwd2.isEmpty()){
                    JOptionPane.showMessageDialog(this,"���������������������!");
                }else {
                    ps.println("REG1-" + passwd1 + "-" + passwd2);
                    String message = br.readLine();
                    if (message.equals("YES")) {     //�������������һ��
                        ps.println("REG2-" + Id.getText() + "-" + passwd1 + "-" + path);
                        try {
                            message = br.readLine();
                            if (message.equals("EXISTS")) {       //���˻��ѱ�ע��
                                JOptionPane.showMessageDialog(this, "���˺��ѱ�ע�ᣬ����ĺ�����!");
                                Id.setText("");
                                Passwd.setText("");
                                querenPasswd.setText("");
                            } else {                              //δ��ע�ᣬע�����
                                JOptionPane.showMessageDialog(this, "ע��ɹ�!");
                                this.setVisible(false);
                            }
                        } catch (Exception exce) {
                        }
                    } else {      //������������벻һ��
                        JOptionPane.showMessageDialog(this, "������������벻���������ĺ�����!");
                        Id.setText("");
                        Passwd.setText("");
                        querenPasswd.setText("");
                    }
                }
            }catch(Exception exce){}
        }
    }
}