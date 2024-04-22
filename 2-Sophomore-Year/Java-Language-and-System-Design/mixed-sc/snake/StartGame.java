package com.kuang.snake;

import javax.swing.*;

//游戏的主启动类
public class StartGame {
    public StartGame() {
    }

    static final int height = 720;

    public static void main(String[] args) {

        //名称,大小,关闭
        //可见,不变,加组件
        JFrame frame = new JFrame("Java-贪吃蛇小游戏");
        frame.setBounds(0,0,915,height);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        frame.setVisible(true);
        frame.setResizable(true);//窗口大小不可变
        frame.add(new GamePanel());//在窗口中显示游戏界面

        //去边框的操作:frame.setUndecorated(true);
    }
}
