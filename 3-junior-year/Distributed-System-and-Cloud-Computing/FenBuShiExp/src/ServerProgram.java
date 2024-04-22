import java.net.*;
import java.text.SimpleDateFormat;
import java.util.Date;

public class ServerProgram {
    public static void main(String[] args) {
        try {
            // （1）构建 DatagramSocket 对象实例，指定接收的端口号
            int serverPort = 12345;
            DatagramSocket datagramSocket = new DatagramSocket(serverPort);

            // 显示服务器启动成功消息
            System.out.println("服务器启动成功，等待客户端连接...");

            while (true) {
                // （2）构建 DatagramPacket 对象实例，用于重组接收到的消息
                byte[] receiveData = new byte[1024];
                DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);

                // （3）调用 datagramSocket 对象实例的 receive 方法，进行消息接收，并将 DatagramPacket 对象实例作为参数
                datagramSocket.receive(receivePacket);

                // 处理接收到的数据
                String receivedMessage = new String(receivePacket.getData(), 0, receivePacket.getLength());

                // 获取当前时间
                Date currentTime = new Date();
                SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
                String formattedTime = dateFormat.format(currentTime);

                // 显示客户端发送的消息和发送时间
                System.out.println("从客户端收到消息(" + formattedTime + "): " + receivedMessage);

                // 如果接收到的消息是'quit()'，发送确认消息给客户端并退出循环
                if (receivedMessage.equals("quit()")) {
                    System.out.println("向客户端发送确认消息...");
                    byte[] confirmationData = ("服务器收到 'quit()'，退出中。" + "\n服务器确认时间: " + formattedTime).getBytes();
                    DatagramPacket confirmationPacket = new DatagramPacket(confirmationData, confirmationData.length, receivePacket.getAddress(), receivePacket.getPort());
                    datagramSocket.send(confirmationPacket);

                    // 显示服务器关闭成功消息
                    System.out.println("服务器关闭成功。");
                    break;
                }
            }

            // 关闭 DatagramSocket
            datagramSocket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
