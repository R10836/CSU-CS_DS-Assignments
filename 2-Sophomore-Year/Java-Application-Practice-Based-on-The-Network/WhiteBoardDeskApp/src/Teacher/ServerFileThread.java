/*
* ��Ҫ�����ʦ�˵��ļ����书��
*
* �ļ���������

    �ͻ�������
        �����¿ͻ�������ʱ��ServerFileThread��run()�����������Ӳ�����һ���µ�FileReadAndWrite�̴߳����ļ����䡣

    �ļ�����
        ��FileReadAndWrite��run()�����У������ļ����ͳ��Ⱥ󣬽���Щ��Ϣ���͸����������ͻ��ˡ�
        Ȼ�󣬽����ļ����ݣ��������ݷ��͸����������ͻ��ˣ�ͬʱ���浽�����ļ��С������ļ�\��ʦ���С�
        �ļ�������Ϻ�ͨ��MyRecorder���Ž��յ���¼���ļ���

    �ֶ��ļ�����
        outFileToClient���������ֶ�����ָ��·�����ļ������пͻ��ˡ���ȡ�ļ����ͳ��Ⱥ󣬽���Щ��Ϣ���͸����пͻ��ˣ�Ȼ���ȡ�ļ����ݲ����͡�
* */

package Teacher;

import Student.MyRecorder;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class ServerFileThread extends Thread{
	ServerSocket server = null;  // ���ڼ����ͻ������ӵķ������׽��֡�
	Socket socket = null;  //  ������ͻ���ͨ�ŵ��׽���
	static List<Socket> list = new ArrayList<Socket>();  // ���ڴ洢�������ӵĿͻ����׽��֡�

	public void run() {
		try {
			server = new ServerSocket(10111);  //��ʼ���������׽��֣������˿�10111��
			while(true) {
				//��������ѭ�������ܿͻ������ӣ��������ӵ��׽�����ӵ�list�С�
				socket = server.accept();
				list.add(socket);
				// �����ļ������߳�
				// ÿ�����¿ͻ�������ʱ������һ��FileReadAndWrite�̴߳���ÿͻ��˵��ļ�����
				FileReadAndWrite fileReadAndWrite = new FileReadAndWrite(socket);
				fileReadAndWrite.start();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

class FileReadAndWrite extends Thread{
	private Socket nowSocket = null;  //��ǰ���ӵĿͻ����׽���

	public FileReadAndWrite(Socket socket) {
		this.nowSocket = socket;
	}

	//��¼��
	public void run() {
		try {
			DataInputStream input = null;
			DataOutputStream output = null;
			DataOutputStream fileWriter = null;
			input = new DataInputStream(nowSocket.getInputStream());  // ������
			while (true) {
				// ��ȡ�ļ����ֺ��ļ�����
				String textName = input.readUTF();
				long textLength = input.readLong();
				// �����ļ����ֺ��ļ����ȸ����пͻ���
				for(Socket socket: ServerFileThread.list) {
					output = new DataOutputStream(socket.getOutputStream());  // �����
					if(socket != nowSocket) {  // ���ļ������ļ����ȷ��͸����������ͻ���
						output.writeUTF(textName);
						output.flush();		   //��������
						output.writeLong(textLength);	//д���ļ�����
						output.flush();
					}
				}
				// �����ļ�����
				int length = -1;
				long curLength = 0;
				byte[] buff = new byte[1024];
				File userFile = new File("�����ļ�\\��ʦ");		//�Լ�ҲҪ����һ�ݲ�����
				if(!userFile.exists()) {  // �½���ǰ�û����ļ���
					userFile.mkdirs();
				}
				String file_path = "�����ļ�\\��ʦ\\"+ textName;
				File file = new File(file_path);
				fileWriter = new DataOutputStream(new FileOutputStream(file));
				while ((length = input.read(buff)) > 0) {
					curLength += length;
					for(Socket socket: ServerFileThread.list) {
						output = new DataOutputStream(socket.getOutputStream());  // �����
						if(socket != nowSocket) {  // ���͸������ͻ���
							output.write(buff, 0, length);
							output.flush();
						}
					}
					fileWriter.write(buff, 0, length);
					fileWriter.flush();
					if(curLength == textLength) {  // ǿ���˳����Ѿ�������
						break;
					}
				}
				MyRecorder play_record = new MyRecorder();	//����¼��
				play_record.play(file_path);
			}
		} catch (Exception e) {}
	}

	//����ָ��·�����ļ������пͻ���
	public static void outFileToClient(String path) {
		try {
			File file = new File(path);
			DataInputStream input = null;
			DataOutputStream output = null;
			input = new DataInputStream(new FileInputStream(file));
			// ��ȡ�ļ����ݣ���ͨ��ѭ�����͸��������ӵĿͻ���
			for(Socket socket: ServerFileThread.list) {
				output = new DataOutputStream(socket.getOutputStream());  // �����
				output.writeUTF(file.getName());
				output.flush();		   //��������
				output.writeLong(file.length());	//д���ļ�����
				output.flush();
			}
			// �����ļ�����
			int length = -1;
			long curLength = 0;
			byte[] buff = new byte[1024];
			while ((length = input.read(buff)) > 0) {
				curLength += length;
				for(Socket socket: ServerFileThread.list) {
					output = new DataOutputStream(socket.getOutputStream());  // �����
					output.write(buff, 0, length);
					output.flush();
				}
				if(curLength == file.length()) {  // ǿ���˳����Ѿ�������
					break;
				}
			}
		} catch (Exception e) {}
	}
}