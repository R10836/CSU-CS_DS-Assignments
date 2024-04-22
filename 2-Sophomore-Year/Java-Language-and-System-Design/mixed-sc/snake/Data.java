package com.kuang.snake;

import javax.swing.*;
import java.net.URL;

//数据中心
public class Data {

    //相对路径 tx.jpg
    //绝对路径 / 相当于当前的项目
    //显示在 Data 类所在的包路径下查找
    //ImageIcon 是 Java 中用于在图形界面中显示图片的类
    //java.net.URL 可以用于获取网页内容、下载文件等网络操作
    public static URL headerURL = Data.class.getResource("statics/header.png");
    public static ImageIcon header = new ImageIcon(headerURL);

    public static URL upURL = Data.class.getResource("statics/up.png");
    public static URL up2URL = Data.class.getResource("statics/up2.png");
    public static URL downURL = Data.class.getResource("statics/down.png");
    public static URL down2URL = Data.class.getResource("statics/down2.png");
    public static URL leftURL = Data.class.getResource("statics/left.png");
    public static URL left2URL = Data.class.getResource("statics/left2.png");
    public static URL rightURL = Data.class.getResource("statics/right.png");
    public static URL right2URL = Data.class.getResource("statics/right2.png");

    public static ImageIcon up = new ImageIcon(upURL);
    public static ImageIcon up2 = new ImageIcon(up2URL);
    public static ImageIcon down = new ImageIcon(downURL);
    public static ImageIcon down2 = new ImageIcon(down2URL);
    public static ImageIcon left = new ImageIcon(leftURL);
    public static ImageIcon left2 = new ImageIcon(left2URL);
    public static ImageIcon right = new ImageIcon(rightURL);
    public static ImageIcon right2 = new ImageIcon(right2URL);

    public static URL bodyURL = Data.class.getResource("statics/body.png");
    public static ImageIcon body = new ImageIcon(bodyURL);

    public static URL body2URL = Data.class.getResource("statics/body2.png");
    public static ImageIcon body2 = new ImageIcon(body2URL);

    public static URL foodURL = Data.class.getResource("statics/food.png");
    public static ImageIcon food = new ImageIcon(foodURL);

    public static URL badURL = Data.class.getResource("statics/bad.png");
    public static ImageIcon bad = new ImageIcon(badURL);
}

