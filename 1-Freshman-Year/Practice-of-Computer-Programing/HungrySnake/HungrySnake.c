#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define UP 72 //方向键：上
#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右
#define SPACE 32 //暂停
#define ESC 27 //退出
#define ENTER 13 //确认

#define HANG 34 //游戏区行数
#define LIE 70 //游戏区列数

#define AIR 0 //标记状态为空气
#define WALL 1 //标记状态为墙
#define FOOD 2 //标记状态为食物
#define HEAD 3 //标记状态为蛇头
#define BODY 4 //标记状态为蛇身

struct Snake
{
    int lenth; //蛇身长度
    int x; //蛇头横坐标
    int y; //蛇头纵坐标
}head;

struct Body
{
    int x; //蛇身横坐标
    int y; //蛇身纵坐标
}body[HANG*LIE];

int maps[HANG][LIE];
int best, grade, speed;

void HideCursor();

void JumpTo(int x, int y);

void color(int c);

void InitMap();

void InitSnake();

void InitFood();

void PrintSnake(int flag);

void AutoMove(int x, int y);

void Move(int x, int y);

void BeforeGame();

void Game();

void AfterGame(int x, int y);

void ReadGrade();

void WriteGrade();

int main()
{
    best = 0, grade = 0;
    srand((unsigned int)time(NULL)); //为rand()随机生成“食物”设置随机数生成点
    system("title 贪吃蛇游戏-已改"); //窗口命名
    system("mode con cols=140 lines=35"); //设置窗口大小
    HideCursor();
    BeforeGame();
    return 0;
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.dwSize = 1;
    curInfo.bVisible = FALSE;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &curInfo);
}

void JumpTo(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, c);
}

void color(int c) //参数c为一个表示相应颜色的十进制数
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void InitMap()
{
    color(120); //背景色设置
    for (int i = 0; i < HANG; i++)
    {
        for (int j = 0; j < LIE; j++)
        {
            if (j == 0 || j == LIE - 1)
            {
                maps[i][j] = WALL; //纵向的墙
                JumpTo(2 * j, i);
                printf("■");
            }
            else if (i == 0 || i == HANG - 1)
            {
                maps[i][j] = WALL; //横向的墙
                printf("■");
            }
            else //背景
            {
                maps[i][j] = AIR;
                printf("  ");
            }
        }
    }
    color(112); //文字提示
    JumpTo(2 , HANG);
    printf("当前得分:%d分", grade);
    JumpTo(LIE / 2 , HANG);
    printf("历史最佳:%d分", best);
    JumpTo(2 * LIE - 24 , HANG);
    printf("作者：ryan");
}

void InitSnake()
{
    head.lenth = 2; //蛇身长度的初始化
    head.x = LIE / 2; //蛇头位置的横坐标的初始化
    head.y = HANG / 2; //蛇头位置的纵坐标的初始化
    
    body[0].x = head.x - 1; //初始的那2节蛇身坐标的初始化
    body[0].y = head.y;
    body[1].x = head.x - 2;
    body[1].y = head.y;
    
    maps[head.y][head.x] = HEAD;
    maps[body[0].y][body[0].x] = BODY;
    maps[body[1].y][body[1].x] = BODY;
}

void InitFood()
{
    int i, j;
    do
    {
        i = rand() % HANG; //随机生成食物的横纵坐标
        j = rand() % LIE;
    } while (maps[i][j] != AIR); //判断生成食物的位置是否为空，只有空位置才能生成
    maps[i][j] = FOOD;
    color(116); //打印食物字符
    JumpTo(2 * j, i);
    printf("★");
}

void PrintSnake(int flag)
{
    if (flag == 1) //打印新蛇头蛇
    {
        color(114);
        JumpTo(2 * head.x, head.y);
        printf("◆");
        for (int i = 0; i < head.lenth; i++)
        {
            JumpTo(2 * body[i].x, body[i].y);
            printf("◆");
        }
    }
    else //打印空格覆盖原蛇身最后一节
    {
        if (body[head.lenth - 1].x != 0)
        {
            JumpTo(2 * body[head.lenth - 1].x, body[head.lenth - 1].y);
            printf("  ");
        }
    }
}

void AutoMove(int x, int y)
{ 
    while (1)
    {
        int flag = 0;
        int time = speed;
        //当time自减为0时跳出while，所以time越小，蛇移动速度越快。因此speed越小，蛇移动速度越快
        while (time--)
        {
            //调用头文件<conio.h>中kbhit()函数，检查当前是否有键盘输入，若有则返回一个非0值，否则返回0
            if (kbhit() != 0)
            {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            AfterGame(x, y); //先判断到达该位置后，是否得分与游戏结束
            Move(x, y); //再移动蛇
        }
        if (flag == 1)
        {
            break; //通过break跳出while(1),这里返回的是函数Game()读取这个键值
        }
    }
}

void Move(int x, int y)
{
    PrintSnake(0); //先消除当前所显示蛇的蛇身最后一节
    maps[body[head.lenth - 1].y][body[head.lenth - 1].x] = AIR; //蛇移动后蛇尾重新标记为空
    maps[head.y][head.x] = BODY; //蛇移动后蛇头的位置变为蛇身第一节
    //重新修改各个坐标
    for (int i = head.lenth - 1; i > 0; i--)
    {
        body[i].x = body[i - 1].x;
        body[i].y = body[i - 1].y;
    }
    body[0].x = head.x;
    body[0].y = head.y;
    head.x = head.x + x;
    head.y = head.y + y;
    PrintSnake(1); //再打印出新的蛇头
}

void BeforeGame()
{
    //做出游戏前的界面
    color(112);
    for(int i = 0; i < HANG + 1; i++)
        for(int j = 0; j < LIE; j++)
            printf("  ");
    JumpTo(LIE - 9 , 6);
    printf("贪 吃 蛇 游 戏");
    JumpTo(LIE - 8 , HANG -18);
    printf("游 戏 操 作");
    JumpTo(LIE - 26 , HANG - 16);
    printf("  吃一颗星得1分  蛇头撞墙或撞到身体则游戏结束");
    JumpTo(LIE - 26 , HANG - 14);
    printf("方向键↑↓←→控制蛇的移动  空格键SPACE暂停游戏");
    JumpTo(LIE - 24 , HANG - 12);
    printf("请按以下数字键开始游戏...退出游戏请按ESC键...");
    JumpTo(LIE - 12 , HANG - 10);
    printf("1————新手模式");
    JumpTo(LIE - 12 , HANG - 8);
    printf("2————老手模式");
    JumpTo(LIE - 12 , HANG - 6);
    printf("3————神手模式");
    JumpTo(2 * LIE - 24 , HANG - 1);
    printf("作者：ryan");
    //实现游戏前的界面的功能
    int n;
    while(1)
    {
        n = getch();
        if (n == ESC)
        {
            system("cls");
            JumpTo(LIE - 6 , HANG / 2);
            printf("游 戏 结 束 ！\a");
            JumpTo(0, HANG - 1);
            exit(0);
        }
        else if (n == '1' || n == '2' || n == '3' )
        {   
            switch(n) //选择蛇的移动速度
            {
                case '1': speed = 4096; break;
                case '2': speed = 2048; break;
                case '3': speed = 1024; break;
            }
            system("cls");
            ReadGrade(); //从文件读取最高分
            InitMap(); //初始化地图
            InitSnake(); //初始化蛇
            PrintSnake(1);
            InitFood(); //初始化食物
            Game(); //开始游戏;
        }
        else
        {
            printf("\a"); //响一声铃提醒玩家
        }
    }
}

void Game()
{
    int n; //初始伪键值（n）
    int tmp = RIGHT; //初始移动方向（tmp）
    AutoMove(1, 0); //游戏刚开始时蛇向右跑
    while (1)
    {
        n = getch();
        //游戏中防止其他键捣乱
        if(n != UP && n != DOWN && n != RIGHT && n != LEFT && n != SPACE && n != ESC)
        {
            n = tmp;
        }
        switch (n)
        {
        case UP: //当按了向上键时
            if (tmp != DOWN) //蛇正在移动的方向是向下时不能改变蛇的方向，即防止蛇出现“原地调头”
            {
                AutoMove(0, -1); //向上移动
                tmp = UP; //记录当前蛇的移动方向
            }
            else
            {
                n = tmp; //按键“无效”，还是向下移动
                AutoMove(0, 1);
            }
            break;
        case DOWN:
            if (tmp != UP)
            {
                AutoMove(0, 1);
                tmp = DOWN;
            }
            else
            {
                n = tmp;
                AutoMove(0 ,-1);
            }
            break;
        case LEFT:
            if (tmp != RIGHT)
            {
                AutoMove(-1, 0);
                tmp = LEFT;
            }
            else
            {
                n = tmp;
                AutoMove(1, 0);
            }
            break;
        case RIGHT:
            if (tmp != LEFT)
            {
                AutoMove(1, 0);
                tmp = RIGHT;
            }
            else
            {
                n = tmp;
                AutoMove(-1, 0);
            }
            break;
        case SPACE:
            system("pause>nul"); //暂停后按任意键继续
            break;
        case ESC:
            system("cls"); //清空屏幕并生成游戏结束画面
            color(112);
            JumpTo(LIE - 6 , HANG / 2);
            printf("游 戏 结 束 ！\a");
            JumpTo(0, HANG - 1);
            exit(0);
        }
    }
}

void AfterGame(int x, int y)
{
    //若蛇头即将到达的位置是食物，则：蛇身长度加一，得分加一，随机生成一个食物
    if (maps[head.y + y][head.x + x] == FOOD)
    {
        head.lenth++; //蛇身长度加一
        grade += 1; //得分加一并实时更新
        color(112);
        JumpTo(2 , HANG);
        printf("当前得分:%d分", grade);
        InitFood(); //随机生成食物
    }
    //若蛇头即将到达的位置是墙或者蛇身，则游戏结束
    else if (maps[head.y + y][head.x + x] == WALL || maps[head.y + y][head.x + x] == BODY)
    {
        system("cls");
        color(112);
        JumpTo(LIE - 6 , 6);
        printf("游 戏 结 束 ！\a"); //响一声铃提醒玩家
        JumpTo(2 * LIE - 24 , HANG - 1);
        printf("作者：大ryan");
        JumpTo(LIE - 18 , HANG / 2);
        if (grade > best)
        {
            printf(" 您已经刷新了最高记录！您的分数是%d分", grade);
            WriteGrade();
        }
        else if(grade == best)
        {
            printf(" 您已经追平了最高纪录！您的分数是%d分", grade);
        }
        else
        {
            printf(" 您的分数是%d分！还差%d分才能追平记录", grade , best - grade);
        }
        int n; //读取键值看是再来一局还是退出游戏
        while (1)
        {
            JumpTo(LIE - 20 , HANG - 6);
            printf("重新开始游戏请按ENTER键...退出游戏请按ESC键...");
            n = getch();
            if (n == ESC)
            {
                JumpTo(0, HANG - 1);
                exit(0);
            }
            else if (n == ENTER)
            {
                system("cls");
                main();
            }
            else
            {
                printf("\a"); //响一声铃提醒玩家
            }
        }
    }
}

void ReadGrade()
{
    FILE* pf = fopen("TheSnake_HighLight_By.txt", "r");
    if (pf == NULL)
    {
        pf = fopen("TheSnake_HighLight_By.txt", "w");
        fwrite(&best, sizeof(int), 1, pf);
    }
    fseek(pf, 0, SEEK_SET);
    fread(&best, sizeof(int), 1, pf);
    fclose(pf);
    pf = NULL;
}

void WriteGrade()
{
    FILE* pf = fopen("TheSnake_HighLight_By.txt", "w");
    if (pf == NULL)
    {
        printf("\a");
        exit(0);
    }
    fwrite(&grade, sizeof(int), 1, pf);
    fclose(pf);
    pf = NULL;
}
