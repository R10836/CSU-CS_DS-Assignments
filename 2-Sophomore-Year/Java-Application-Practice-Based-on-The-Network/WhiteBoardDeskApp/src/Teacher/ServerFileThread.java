/*
* 主要负责教师端的文件传输功能
*
* 文件传输流程

    客户端连接
        当有新客户端连接时，ServerFileThread的run()方法接受连接并启动一个新的FileReadAndWrite线程处理文件传输。

    文件发送
        在FileReadAndWrite的run()方法中，接收文件名和长度后，将这些信息发送给所有其他客户端。
        然后，接收文件内容，并将内容发送给所有其他客户端，同时保存到本地文件夹“接收文件\教师”中。
        文件接收完毕后，通过MyRecorder播放接收到的录音文件。

    手动文件发送
        outFileToClient方法用于手动发送指定路径的文件给所有客户端。读取文件名和长度后，将这些信息发送给所有客户端，然后读取文件内容并发送。
* */

package Teacher;

import Student.MyRecorder;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class ServerFileThread extends Thread{
	ServerSocket server = null;  // 用于监听客户端连接的服务器套接字。
	Socket socket = null;  //  用于与客户端通信的套接字
	static List<Socket> list = new ArrayList<Socket>();  // 用于存储所有连接的客户端套接字。

	public void run() {
		try {
			server = new ServerSocket(10111);  //初始化服务器套接字，监听端口10111。
			while(true) {
				//进入无限循环，接受客户端连接，并将连接的套接字添加到list中。
				socket = server.accept();
				list.add(socket);
				// 开启文件传输线程
				// 每次有新客户端连接时，启动一个FileReadAndWrite线程处理该客户端的文件传输
				FileReadAndWrite fileReadAndWrite = new FileReadAndWrite(socket);
				fileReadAndWrite.start();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

class FileReadAndWrite extends Thread{
	private Socket nowSocket = null;  //当前连接的客户端套接字

	public FileReadAndWrite(Socket socket) {
		this.nowSocket = socket;
	}

	//发录音
	public void run() {
		try {
			DataInputStream input = null;
			DataOutputStream output = null;
			DataOutputStream fileWriter = null;
			input = new DataInputStream(nowSocket.getInputStream());  // 输入流
			while (true) {
				// 获取文件名字和文件长度
				String textName = input.readUTF();
				long textLength = input.readLong();
				// 发送文件名字和文件长度给所有客户端
				for(Socket socket: ServerFileThread.list) {
					output = new DataOutputStream(socket.getOutputStream());  // 输出流
					if(socket != nowSocket) {  // 将文件名和文件长度发送给所有其他客户端
						output.writeUTF(textName);
						output.flush();		   //清空输出流
						output.writeLong(textLength);	//写入文件长度
						output.flush();
					}
				}
				// 发送文件内容
				int length = -1;
				long curLength = 0;
				byte[] buff = new byte[1024];
				File userFile = new File("接收文件\\教师");		//自己也要保存一份并播放
				if(!userFile.exists()) {  // 新建当前用户的文件夹
					userFile.mkdirs();
				}
				String file_path = "接收文件\\教师\\"+ textName;
				File file = new File(file_path);
				fileWriter = new DataOutputStream(new FileOutputStream(file));
				while ((length = input.read(buff)) > 0) {
					curLength += length;
					for(Socket socket: ServerFileThread.list) {
						output = new DataOutputStream(socket.getOutputStream());  // 输出流
						if(socket != nowSocket) {  // 发送给其它客户端
							output.write(buff, 0, length);
							output.flush();
						}
					}
					fileWriter.write(buff, 0, length);
					fileWriter.flush();
					if(curLength == textLength) {  // 强制退出，已经发完了
						break;
					}
				}
				MyRecorder play_record = new MyRecorder();	//播放录音
				play_record.play(file_path);
			}
		} catch (Exception e) {}
	}

	//发送指定路径的文件给所有客户端
	public static void outFileToClient(String path) {
		try {
			File file = new File(path);
			DataInputStream input = null;
			DataOutputStream output = null;
			input = new DataInputStream(new FileInputStream(file));
			// 读取文件内容，并通过循环发送给所有连接的客户端
			for(Socket socket: ServerFileThread.list) {
				output = new DataOutputStream(socket.getOutputStream());  // 输出流
				output.writeUTF(file.getName());
				output.flush();		   //清空输出流
				output.writeLong(file.length());	//写入文件长度
				output.flush();
			}
			// 发送文件内容
			int length = -1;
			long curLength = 0;
			byte[] buff = new byte[1024];
			while ((length = input.read(buff)) > 0) {
				curLength += length;
				for(Socket socket: ServerFileThread.list) {
					output = new DataOutputStream(socket.getOutputStream());  // 输出流
					output.write(buff, 0, length);
					output.flush();
				}
				if(curLength == file.length()) {  // 强制退出，已经发完了
					break;
				}
			}
		} catch (Exception e) {}
	}
}