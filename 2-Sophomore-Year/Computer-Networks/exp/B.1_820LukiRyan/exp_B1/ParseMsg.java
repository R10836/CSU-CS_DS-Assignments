// 解析信息类
public class ParseMsg
{
    private String method; //消息的类型
    private String target=null; // 消息的目标方
    private String sourse=null; // 消息的发送方
    private String msg=null; // 消息的内容

    public ParseMsg(String msg/* 要解析的字符串msg */)
    {
        this.method=msg.split("/")[0]; // 将字符串 msg 使用 / 分割，并将分割后的第一个部分（索引为 0）赋值给成员变量 method，表示消息的类型或方法。
        this.sourse=msg.split("/")[1]; // 将字符串 msg 使用 / 分割，并将分割后的第二个部分（索引为 1）赋值给成员变量 source，表示消息的发送方。
        this.target=msg.split("/")[2]; // 将字符串 msg 使用 / 分割，并将分割后的第三个部分（索引为 2）赋值给成员变量 target，表示消息的目标方。
        this.msg=msg.split(msg.split("/")[2]+"/")[1]; // 使用 / 分割字符串 msg，然后使用分割后的第三个部分（索引为 2）拼接成一个子字符串，再将该子字符串使用 / 分割，并取分割后的第二个部分（索引为 1），最后将该部分赋值给成员变量 msg，表示消息的内容。
        System.out.println(msg+"   "+this.getMsg());
        /* 例：

            输入：BROADCAST/User1/Group1/Hello, everyone!

            输出：
            内容：Hello, everyone!
            类型：BROADCAST
            发送方：User1
            目标方：Group1
        */
    }

    // 获取信息类型
    public String getMethod()
    {
        return this.method;
    }
    // 获取信息发送方
    public String getSourse()
    {
        return this.sourse;
    }
    // 获取信息目标方
    public String getTarget()
    {
        return this.target;
    }
    // 获取信息内容
    public String getMsg()
    {
        return this.msg;
    }
}