import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class ReceiveMessage {
    public static void main(String[] args) throws IOException {

        //1.创建DatagramSocket对象
        DatagramSocket ds = new DatagramSocket(10086);

        //2.接受数据包
        byte[] bytes = new byte[1024];
        DatagramPacket dp = new DatagramPacket(bytes, bytes.length);

        while (true) {
            ds.receive(dp);

            //3.解析数据包
            byte[] data = dp.getData();
            int len = dp.getLength();
            String ip = dp.getAddress().getHostAddress();
            String hostName = dp.getAddress().getHostName();

            //4.打印数据
            System.out.println("ip为" + ip + "，主机名为" + hostName + "的人，发送了长度为" + len + "的数据：" + new String(data, 0 ,len));
        }
    }
}
