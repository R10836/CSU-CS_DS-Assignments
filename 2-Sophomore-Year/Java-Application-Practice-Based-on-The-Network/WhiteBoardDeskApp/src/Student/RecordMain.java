//¼����ҳ����ʾ

package Student;

import Student.MyRecorder;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
public class RecordMain extends JFrame implements ActionListener{
    private JButton beginBtn = new JButton("��ʼ¼��");
    private JButton stopBtn = new JButton("ֹͣ¼��");
    private MyRecorder Recorder1 = new MyRecorder();
    public static Boolean flag = false;
    public RecordMain(){
        Font font = new Font("΢���ź�", Font.BOLD, 30);
        this.setLayout(null);
        beginBtn.setSize(300,140);
        beginBtn.setLocation(0,0);
        beginBtn.addActionListener(this);
        beginBtn.setFont(font);
        stopBtn.addActionListener(this);
        stopBtn.setSize(300,140);
        stopBtn.setFont(font);
        stopBtn.setLocation(0,0);
        stopBtn.setVisible(false);
        this.add(beginBtn);
        this.add(stopBtn);
        this.setTitle("�ȴ���ʼ¼������");
        this.setSize(310,176);
        this.setVisible(true);
    }
    public void actionPerformed(ActionEvent e){
        if(e.getSource() == beginBtn){
            Recorder1.start();
            stopBtn.setVisible(true);
            beginBtn.setVisible(false);
            this.setTitle("����¼���С���");
        }else{
            stopBtn.setVisible(false);
            beginBtn.setVisible(true);
            Recorder1.stop();
            flag = true;        //����¼����
            this.setVisible(false);
        }
    }
}