import java.net.*;
import java.util.Scanner;

public class ClientProgram {
    public static void main(String[] args) {
        System.out.println("客户端启动成功！ (输入'quit()'退出)");
        try {
            // （1）构建 DatagramSocket 对象实例
            DatagramSocket datagramSocket = new DatagramSocket();

            // 获取用户输入
            Scanner scanner = new Scanner(System.in);

            while (true) {
                System.out.print("请输入要发送的消息: ");
                String message = scanner.nextLine();

                // （2）构建 DatagramPacket 对象实例，包含接收者主机地址、接收端口号等信息
                InetAddress receiverAddress = InetAddress.getByName("localhost"); // 或者 InetAddress.getByName("127.0.0.1");
                int receiverPort = 12345;
                byte[] data = message.getBytes();
                DatagramPacket datagramPacket = new DatagramPacket(data, data.length, receiverAddress, receiverPort);

                // （3）调用 datagramSocket 对象实例的 send 方法，将 DatagramPacket 对象实例作为参数发送
                datagramSocket.send(datagramPacket);

                // 如果用户输入'quit()'，退出循环
                if (message.equals("quit()")) {
                    break;
                }
            }

            // 关闭 Scanner 和 DatagramSocket
            scanner.close();
            datagramSocket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
