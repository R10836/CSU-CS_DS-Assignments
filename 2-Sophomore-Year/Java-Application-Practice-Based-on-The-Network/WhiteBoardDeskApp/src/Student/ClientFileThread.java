//学生端接收文件

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
	static PrintStream out = null; 		 //普通消息的发送，即文件/语音消息发送提醒在各个客户端的展示
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

	// 客户端接收文件
	public void run() {
		try {
			InetAddress addr = InetAddress.getByName(null);  // 获取主机地址
			socket = new Socket(addr, 10111);  // 客户端套接字
			fileIn = new DataInputStream(socket.getInputStream());  // 输入流
			fileOut = new DataOutputStream(socket.getOutputStream());  // 输出流
			// 接收文件
			while(true) {
				String textName = fileIn.readUTF();
				long totalLength = fileIn.readLong();
				int length = -1;
				byte[] buff = new byte[1024];
				long curLength = 0;

				int result = JOptionPane.showConfirmDialog(chatViewJFrame, "您是否接收？", "接收提醒",
														   JOptionPane.YES_NO_OPTION);
				// 提示框选择结果，0为确定，1为取消
				if(result == 0){
					File userFile = new File("接收文件\\" + NickName);
					if(!userFile.exists()) {  // 新建当前用户的文件夹
						userFile.mkdirs();
					}
					file_path = "接收文件\\" + NickName + "\\"+ textName;
					File file = new File(file_path);
					fileWriter = new DataOutputStream(new FileOutputStream(file));
					while((length = fileIn.read(buff)) > 0) {  // 把文件写进本地
						fileWriter.write(buff, 0, length);
						fileWriter.flush();
						curLength += length;
						if(curLength == totalLength) {  // 强制结束
							break;
						}
					}
					//判断文件后缀，从而知道是语音还是文件
					String fileExtension = file_path.substring(file_path.lastIndexOf('.') + 1);
					if(fileExtension.equals("mp3")) {
						// 播放语音
						MyRecorder play_record = new MyRecorder();
						play_record.play(file_path);
					}else{
						//打开文本文件
						File file1 = new File(file_path);
						Desktop desktop = Desktop.getDesktop();
						try{
							if(file1.exists())
								desktop.open(file1);
						}catch(Exception exc){}
					}
					fileWriter.close();
				}
				else {  // 不接收文件
					while((length = fileIn.read(buff)) > 0) {
						curLength += length;
						if(curLength == totalLength) {  // 强制结束
							break;
						}
					}
				}
			}
		} catch (Exception e) {}
	}

	// 客户端发送文件
	public static void outFileToServer(String path) {
		try {
			File file = new File(path);
			fileReader = new DataInputStream(new FileInputStream(file));
			fileOut.writeUTF(file.getName());  // 发送文件名字
			fileOut.flush();
			fileOut.writeLong(file.length());  // 发送文件长度
			fileOut.flush();
			int length = -1;
			byte[] buff = new byte[1024];
			while ((length = fileReader.read(buff)) > 0) {  // 发送内容
				fileOut.write(buff, 0, length);
				fileOut.flush();
			}
			out.println(NickName + "-[发言接收提醒]我发送了一条发言。");
		} catch (Exception e) {}
	}
}
