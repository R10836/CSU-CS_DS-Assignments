/*1.定义数据
  2.画上去
  3.监听事件
      键盘
      事件
 */
/*
1.初始化，包括创建窗口、加载资源等。
2.开始游戏，初始化蛇、大迷糊和食物，判定大迷糊的移动方式和转向条件，并启动计时器动态更新界面。
3.蛇吃到食物后长度加1，再重新生成食物。
4.通过方向键控制蛇的移动，蛇碰到边界、自身或者大迷糊游戏结束。
5.分数计算根据蛇的长度得分，游戏结束后可记录最高分。
 */
/*
javax.swing.*: 引入Swing界面组件库，包括JFrame（窗口）、JPanel（面板）、JLabel（标签）等组件。
java.awt.*: 引入AWT组件库，提供更底层的窗口和图形处理功能。
java.awt.event.ActionEvent: 引入ActionEvent事件，表示动作事件。
java.awt.event.ActionListener: 引入ActionListener接口，表示监听动作事件的接口。
java.awt.event.KeyEvent: 引入KeyEvent事件，表示键盘事件。
java.awt.event.KeyListener: 引入KeyListener接口，表示监听键盘事件的接口。
java.util.Random: 引入Random类，用于生成随机数。
javax.swing.Timer: 引入Swing中的Timer类，可以定时触发事件，用于实现计时器等相关功能。
*/
package com.kuang.snake;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.Random;
import javax.swing.Timer;

public class GamePanel extends JPanel implements KeyListener , ActionListener {

    //******************定义蛇的数据结构********************
    int length;//蛇的长度
    int length2=10;//大迷糊的长度
    int [] snakeX = new int[600];//蛇的x坐标25*25
    int [] snakeY = new int[600];//蛇的y坐标25*25
    String fx ;//蛇头方向可以取值"R"(右)、"L"(左)、"U"(上)、"D"(下)四个
    int fx2 ;//大迷糊蛇头方向，0、1、2、3分别对应右、左、上、下四个方向

    //食物的坐标
    int foodx;
    int foody;
    Random random =new Random();//初始值由Random类生成
    int score;//成绩
    //游戏当前的状态:开始,停止
    boolean isStart = false;//默认不开始
    boolean isFail = false;
    //定时器
    Timer Timer = new Timer(100,this);//100ms执行一次,控制蛇移动的速度
    //大迷糊的坐标数组
    int [] badX = new int[length2];
    int [] badY = new int[length2];

    static  int a=0;
    //**********************构造器**************************
    public GamePanel(){
        //初始化游戏
        init();//初始化方法，重置游戏状态
        //获得焦点和键盘事件
        this.setFocusable(true);
        this.addKeyListener(this);//键盘监听器，即当用户按下键盘键时，程序可根据具体操作进行响应。
        //游戏一开始定时器就启动
        Timer.start();
    }
    //********************初始化方法**************************
    public void init(){
        //贪吃蛇初始位置
        snakeX[0] = 100 ;snakeY[0] = 100 ;//脑袋的坐标
        snakeX[1] = 75 ;snakeY[1] = 100 ;//第一个身体坐标
        snakeX[2] = 50 ;snakeY[2] = 100 ;//第二个身体坐标
        fx = "R";//初始方向向右

        //大迷糊初始位置
        badX[0] = 450 ;
        badY[0] = 350 ;
        for (int i = 1; i < length2; i++) {//length2=10
            badX[i] = badX[i-1] -25;//身体水平，每个节点间隔25个像素
            badY[i] = badY[i-1] ;
        }
        fx2 = 1 ;//方向向左
        //把食物放在界面上
        foodx=25+25*random.nextInt(34);
        foody=75+25*random.nextInt(24);

        //长度,分数
        length = 3;
        score=0;
    }


    //*******************绘制面板,画笔**********************
    @Override
    protected void paintComponent(Graphics g){
        //函数用于在组件上实现GUI动画效果、自定义控件和其他可视化效果，它会被自动调用以绘制组件
        super.paintComponent(g);//清屏
        //绘制静态的面板
        this.setBackground(Color.GRAY);
        //Data.header.paintIcon(this,g,25,11);//头部广告栏画上去
        g.fillRect(25,75,850,600);//默认的游戏界面

        //画积分
        g.setColor(Color.WHITE);
        g.setFont(new Font("微软雅黑",Font.BOLD,30));
        g.drawString("长度"+length,500,45);
        g.drawString("分数"+score,660,45);
        //先画食物
        Data.food.paintIcon(this,g,foodx,foody);

        //画贪吃蛇,RLUD与键盘的右左上下联系起来
        if(fx.equals("R")){
            Data.right.paintIcon(this,g,snakeX[0],snakeY[0]);//蛇头初始化向右,需要通过方向来判断
        }else if(fx.equals("L")){
            Data.left.paintIcon(this,g,snakeX[0],snakeY[0]);//蛇头初始化向右,需要通过方向来判断
        }else if(fx.equals("U")){
            Data.up.paintIcon(this,g,snakeX[0],snakeY[0]);//蛇头初始化向右,需要通过方向来判断
        }else if(fx.equals("D")){
            Data.down.paintIcon(this,g,snakeX[0],snakeY[0]);//蛇头初始化向右,需要通过方向来判断
        }
        //使用 Data.body 变量存储了贪吃蛇身体的图标（图片），并调用 paintIcon() 方法将图标绘制到程序界面上
        for (int i = 1; i < length; i++) {//画贪吃蛇身体,初始为1
            Data.body.paintIcon(this,g,snakeX[i],snakeY[i]);
        }

        //大迷糊的走法,在画之前确定好方向

        if(isStart&&isFail==false){
            if(a%10==0){
                int r = (random.nextInt(2)) % 2;//直接nextInt会产生负数//不含bound
                fx2 = (fx2+r)%4;
            }//不会是与上次相反的方向0123上右下左
            a++;
            switch (fx2) {
                case 0:
                    badY[0] = badY[0] - 25;
                    break;//上
                case 1:
                    badX[0] = badX[0] + 25;
                    break;//右
                case 2:
                    badY[0] = badY[0] + 25;
                    break;//下
                case 3:
                    badX[0] = badX[0] - 25;
                    break;//左
            }
            //撞墙判定
            if(badX[0]>850-25) {
                badX[0] = badX[0] - 25;//复原,重选方向
                int rr=(random.nextInt(2));
                switch(rr){
                    case 0:fx2=2;badY[0]=badY[0]+25;break;//下
                    case 1:fx2=0;badY[0]=badY[0]-25;break;//上
                }
            }
            if(badX[0]<25+25) {
                badX[0] = badX[0] + 25;
                int rr=(random.nextInt(2));
                switch(rr){
                    case 0:fx2=2;badY[0]=badY[0]+25;break;//下
                    case 1:fx2=0;badY[0]=badY[0]-25;break;//上
                }
            }
            if(badY[0]>650-25) {
                badY[0] = badY[0] - 25;
                int rr=(random.nextInt(2));
                switch(rr){
                    case 0:fx2=1;badX[0]=badX[0]+25;break;//右
                    case 1:fx2=3;badX[0]=badX[0]-25;break;//左
                }
            }
            if(badY[0]<75+25) {
                badY[0] = badY[0] + 25;
                int rr=(random.nextInt(2));
                switch(rr){
                    case 0:fx2=1;badX[0]=badX[0]+25;break;//右
                    case 1:fx2=3;badX[0]=badX[0]-25;break;//左
                }
            }

//            System.out.println("前.[0]"+badX[0]);
//            System.out.println("前.[1]"+badX[1]);

            //大迷糊移动
            for(int i=length2-1;i>0;i--){//后一节移到前一节的位置
                badX[i]=badX[i-1];
                badY[i]=badY[i-1];
            }
            //中间断了一节debug
            switch (fx2) {
                case 0:
                    badY[1]=badY[1]+25;
                    break;//上
                case 1:
                    badX[1]=badX[1]-25;
                    break;//右
                case 2:
                    badY[1]=badY[1]-25;
                    break;//下
                case 3:
                    badX[1]=badX[1]+25;
                    break;//左
            }
//            System.out.println("后.[0]"+badX[0]);
//            System.out.println("后.[1]"+badX[1]);
//            System.out.println("**************");
        }

        //算法放在画大迷糊之前,确定好了才开始画
        //画大迷糊
        for (int i = 1; i < length2; i++) {//画身体,初始为1
            Data.body2.paintIcon(this,g,badX[i],badY[i]);
        }

        switch(fx2){
            case 1:Data.right2.paintIcon(this,g,badX[0],badY[0]);break;//右
            case 3:Data.left2.paintIcon(this,g,badX[0],badY[0]);break;//左
            case 2:Data.down2.paintIcon(this,g,badX[0],badY[0]);break;//下
            case 0:Data.up2.paintIcon(this,g,badX[0],badY[0]);break;//上

        }

        //游戏状态,开始,失败
        if(isStart ==false){
            g.setColor(Color.white);
            g.setFont(new Font("微软雅黑",Font.BOLD,40));//设置字体
            g.drawString("按下空格开始游戏",300,300);
        }
        if(isFail){
            g.setColor(Color.RED);
            g.setFont(new Font("微软雅黑",Font.BOLD,40));//设置字体
            g.drawString("失败,按下空格重新开始",300,300);
        }
    }


    @Override
    public void keyTyped(KeyEvent e) {

    }

    //键盘监听事件
    @Override
    public void keyPressed(KeyEvent e) {
        int keyCode = e.getKeyCode();//获取用户按下的键盘
        if(keyCode == KeyEvent.VK_SPACE){//按键为空格
            if(isFail){
                //失败则重新开始
                isFail=false;
                init();
            } else {//切换为暂停或继续游戏
                isStart = !isStart;
            }

            repaint();//刷新界面
        }
        //小蛇移动
        if(keyCode==KeyEvent.VK_UP){
            fx = "U";
        } else if (keyCode==KeyEvent.VK_DOWN) {
            fx = "D";
        }else if (keyCode==KeyEvent.VK_LEFT) {
            fx = "L";
        }else if (keyCode==KeyEvent.VK_RIGHT) {
            fx = "R";
        }


    }

    @Override
    public void keyReleased(KeyEvent e) {

    }

    //事件监听,需要通过固定事件来刷新,1s=10次
    @Override
    public void actionPerformed(ActionEvent e) {
        if(isStart&&isFail==false){//处于开始且未失败
            //蛇的头部与食物重合，吃事物
            if (snakeX[0] == foodx && snakeY[0] == foody) {
                //变长
                length++;
                //分数加10
                score=score+10;
                //再次随机生成食物
                foodx=25+25*random.nextInt(34);
                foody=75+25*random.nextInt(24);
            }
            //贪吃蛇移动
            for(int i=length-1;i>0;i--){//后一节移到前一节的位置
                snakeX[i]=snakeX[i-1];
                snakeY[i]=snakeY[i-1];
            }

            //方向，撞到边界则失败
            if(fx.equals("R")){
                snakeX[0]=snakeX[0]+25;
                if(snakeX[0]>850){isFail=true;}//边界判断
            } else if (fx.equals("L")){
                snakeX[0] = snakeX[0]-25;
                if(snakeX[0]<25){isFail=true;}//边界判断
            }else if (fx.equals("U")){
                snakeY[0] = snakeY[0]-25;
                if(snakeY[0]<75){isFail=true;}//边界判断
            }else if (fx.equals("D")){
                snakeY[0] = snakeY[0]+25;
                if(snakeY[0]>650){isFail=true;}//边界判断
            }


        }
        //失败判断,撞到自己失败
        for (int i = 1; i < length; i++) {
            if(snakeX[0]==snakeX[i]&&snakeY[0]==snakeY[i]){
                isFail=true;
            }
        }

        //撞到大迷糊
        for (int i = 0; i < length2; i++) {
            if(snakeX[0]==badX[i]&&snakeY[0]==badY[i]){
                isFail=true;
            }
        }

        repaint();
        Timer.start();//间隔100ms刷新
    }
}
