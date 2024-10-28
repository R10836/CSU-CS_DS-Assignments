//ѧ���˽����ļ�

package Student;

import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.net.InetAddress;
import java.net.Socket;

public class ClientFileThread extends Thread{
	private Socket socket = null;
	private JFrame chatViewJFrame = null;
	static String NickName = null;
	static PrintStream out = null; 		 //��ͨ��Ϣ�ķ��ͣ����ļ�/������Ϣ���������ڸ����ͻ��˵�չʾ
	static DataInputStream fileIn = null;
	static DataOutputStream fileOut = null;
	static DataInputStream fileReader = null;
	static DataOutputStream fileWriter = null;
	private String file_path = null;
	private String s1;
	private String s2;
	public ClientFileThread(String NickName, JFrame chatViewJFrame, PrintStream out) {
		ClientFileThread.NickName = NickName;
		ClientFileThread.out = out;
		this.chatViewJFrame = chatViewJFrame;
	}

	// �ͻ��˽����ļ�
	public void run() {
		try {
			InetAddress addr = InetAddress.getByName(null);  // ��ȡ������ַ
			socket = new Socket(addr, 10111);  // �ͻ����׽���
			fileIn = new DataInputStream(socket.getInputStream());  // ������
			fileOut = new DataOutputStream(socket.getOutputStream());  // �����
			// �����ļ�
			while(true) {
				String textName = fileIn.readUTF();
				long totalLength = fileIn.readLong();
				int length = -1;
				byte[] buff = new byte[1024];
				long curLength = 0;

				int result = JOptionPane.showConfirmDialog(chatViewJFrame, "���Ƿ���գ�", "��������",
														   JOptionPane.YES_NO_OPTION);
				// ��ʾ��ѡ������0Ϊȷ����1Ϊȡ��
				if(result == 0){
					File userFile = new File("�����ļ�\\" + NickName);
					if(!userFile.exists()) {  // �½���ǰ�û����ļ���
						userFile.mkdirs();
					}
					file_path = "�����ļ�\\" + NickName + "\\"+ textName;
					File file = new File(file_path);
					fileWriter = new DataOutputStream(new FileOutputStream(file));
					while((length = fileIn.read(buff)) > 0) {  // ���ļ�д������
						fileWriter.write(buff, 0, length);
						fileWriter.flush();
						curLength += length;
						if(curLength == totalLength) {  // ǿ�ƽ���
							break;
						}
					}
					//�ж��ļ���׺���Ӷ�֪�������������ļ�
					String fileExtension = file_path.substring(file_path.lastIndexOf('.') + 1);
					if(fileExtension.equals("mp3")) {
						// ��������
						MyRecorder play_record = new MyRecorder();
						play_record.play(file_path);
					}else{
						//���ı��ļ�
						File file1 = new File(file_path);
						Desktop desktop = Desktop.getDesktop();
						try{
							if(file1.exists())
								desktop.open(file1);
						}catch(Exception exc){}
					}
					fileWriter.close();
				}
				else {  // �������ļ�
					while((length = fileIn.read(buff)) > 0) {
						curLength += length;
						if(curLength == totalLength) {  // ǿ�ƽ���
							break;
						}
					}
				}
			}
		} catch (Exception e) {}
	}

	// �ͻ��˷����ļ�
	public static void outFileToServer(String path) {
		try {
			File file = new File(path);
			fileReader = new DataInputStream(new FileInputStream(file));
			fileOut.writeUTF(file.getName());  // �����ļ�����
			fileOut.flush();
			fileOut.writeLong(file.length());  // �����ļ�����
			fileOut.flush();
			int length = -1;
			byte[] buff = new byte[1024];
			while ((length = fileReader.read(buff)) > 0) {  // ��������
				fileOut.write(buff, 0, length);
				fileOut.flush();
			}
			out.println(NickName + "-[���Խ�������]�ҷ�����һ�����ԡ�");
		} catch (Exception e) {}
	}
}
