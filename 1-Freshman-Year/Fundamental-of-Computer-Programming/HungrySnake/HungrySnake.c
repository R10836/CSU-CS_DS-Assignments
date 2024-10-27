#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define UP 72 //���������
#define DOWN 80 //���������
#define LEFT 75 //���������
#define RIGHT 77 //���������
#define SPACE 32 //��ͣ
#define ESC 27 //�˳�
#define ENTER 13 //ȷ��

#define HANG 34 //��Ϸ������
#define LIE 70 //��Ϸ������

#define AIR 0 //���״̬Ϊ����
#define WALL 1 //���״̬Ϊǽ
#define FOOD 2 //���״̬Ϊʳ��
#define HEAD 3 //���״̬Ϊ��ͷ
#define BODY 4 //���״̬Ϊ����

struct Snake
{
    int lenth; //������
    int x; //��ͷ������
    int y; //��ͷ������
}head;

struct Body
{
    int x; //���������
    int y; //����������
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
    srand((unsigned int)time(NULL)); //Ϊrand()������ɡ�ʳ�������������ɵ�
    system("title ̰������Ϸ-�Ѹ�"); //��������
    system("mode con cols=140 lines=35"); //���ô��ڴ�С
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

void color(int c) //����cΪһ����ʾ��Ӧ��ɫ��ʮ������
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void InitMap()
{
    color(120); //����ɫ����
    for (int i = 0; i < HANG; i++)
    {
        for (int j = 0; j < LIE; j++)
        {
            if (j == 0 || j == LIE - 1)
            {
                maps[i][j] = WALL; //�����ǽ
                JumpTo(2 * j, i);
                printf("��");
            }
            else if (i == 0 || i == HANG - 1)
            {
                maps[i][j] = WALL; //�����ǽ
                printf("��");
            }
            else //����
            {
                maps[i][j] = AIR;
                printf("  ");
            }
        }
    }
    color(112); //������ʾ
    JumpTo(2 , HANG);
    printf("��ǰ�÷�:%d��", grade);
    JumpTo(LIE / 2 , HANG);
    printf("��ʷ���:%d��", best);
    JumpTo(2 * LIE - 24 , HANG);
    printf("���ߣ�r");
}

void InitSnake()
{
    head.lenth = 2; //�����ȵĳ�ʼ��
    head.x = LIE / 2; //��ͷλ�õĺ�����ĳ�ʼ��
    head.y = HANG / 2; //��ͷλ�õ�������ĳ�ʼ��
    
    body[0].x = head.x - 1; //��ʼ����2����������ĳ�ʼ��
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
        i = rand() % HANG; //�������ʳ��ĺ�������
        j = rand() % LIE;
    } while (maps[i][j] != AIR); //�ж�����ʳ���λ���Ƿ�Ϊ�գ�ֻ�п�λ�ò�������
    maps[i][j] = FOOD;
    color(116); //��ӡʳ���ַ�
    JumpTo(2 * j, i);
    printf("��");
}

void PrintSnake(int flag)
{
    if (flag == 1) //��ӡ����ͷ��
    {
        color(114);
        JumpTo(2 * head.x, head.y);
        printf("��");
        for (int i = 0; i < head.lenth; i++)
        {
            JumpTo(2 * body[i].x, body[i].y);
            printf("��");
        }
    }
    else //��ӡ�ո񸲸�ԭ�������һ��
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
        //��time�Լ�Ϊ0ʱ����while������timeԽС�����ƶ��ٶ�Խ�졣���speedԽС�����ƶ��ٶ�Խ��
        while (time--)
        {
            //����ͷ�ļ�<conio.h>��kbhit()��������鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0
            if (kbhit() != 0)
            {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            AfterGame(x, y); //���жϵ����λ�ú��Ƿ�÷�����Ϸ����
            Move(x, y); //���ƶ���
        }
        if (flag == 1)
        {
            break; //ͨ��break����while(1),���ﷵ�ص��Ǻ���Game()��ȡ�����ֵ
        }
    }
}

void Move(int x, int y)
{
    PrintSnake(0); //��������ǰ����ʾ�ߵ��������һ��
    maps[body[head.lenth - 1].y][body[head.lenth - 1].x] = AIR; //���ƶ�����β���±��Ϊ��
    maps[head.y][head.x] = BODY; //���ƶ�����ͷ��λ�ñ�Ϊ�����һ��
    //�����޸ĸ�������
    for (int i = head.lenth - 1; i > 0; i--)
    {
        body[i].x = body[i - 1].x;
        body[i].y = body[i - 1].y;
    }
    body[0].x = head.x;
    body[0].y = head.y;
    head.x = head.x + x;
    head.y = head.y + y;
    PrintSnake(1); //�ٴ�ӡ���µ���ͷ
}

void BeforeGame()
{
    //������Ϸǰ�Ľ���
    color(112);
    for(int i = 0; i < HANG + 1; i++)
        for(int j = 0; j < LIE; j++)
            printf("  ");
    JumpTo(LIE - 9 , 6);
    printf("̰ �� �� �� Ϸ");
    JumpTo(LIE - 8 , HANG -18);
    printf("�� Ϸ �� ��");
    JumpTo(LIE - 26 , HANG - 16);
    printf("  ��һ���ǵ�1��  ��ͷײǽ��ײ����������Ϸ����");
    JumpTo(LIE - 26 , HANG - 14);
    printf("������������������ߵ��ƶ�  �ո��SPACE��ͣ��Ϸ");
    JumpTo(LIE - 24 , HANG - 12);
    printf("�밴�������ּ���ʼ��Ϸ...�˳���Ϸ�밴ESC��...");
    JumpTo(LIE - 12 , HANG - 10);
    printf("1������������ģʽ");
    JumpTo(LIE - 12 , HANG - 8);
    printf("2������������ģʽ");
    JumpTo(LIE - 12 , HANG - 6);
    printf("3��������ʥ��ģʽ");
    JumpTo(2 * LIE - 24 , HANG - 1);
    printf("���ߣ�r");
    //ʵ����Ϸǰ�Ľ���Ĺ���
    int n;
    while(1)
    {
        n = getch();
        if (n == ESC)
        {
            system("cls");
            JumpTo(LIE - 6 , HANG / 2);
            printf("�� Ϸ �� �� ��\a");
            JumpTo(0, HANG - 1);
            exit(0);
        }
        else if (n == '1' || n == '2' || n == '3' )
        {   
            switch(n) //ѡ���ߵ��ƶ��ٶ�
            {
                case '1': speed = 4096; break;
                case '2': speed = 2048; break;
                case '3': speed = 1024; break;
            }
            system("cls");
            ReadGrade(); //���ļ���ȡ��߷�
            InitMap(); //��ʼ����ͼ
            InitSnake(); //��ʼ����
            PrintSnake(1);
            InitFood(); //��ʼ��ʳ��
            Game(); //��ʼ��Ϸ;
        }
        else
        {
            printf("\a"); //��һ�����������
        }
    }
}

void Game()
{
    int n; //��ʼα��ֵ��n��
    int tmp = RIGHT; //��ʼ�ƶ�����tmp��
    AutoMove(1, 0); //��Ϸ�տ�ʼʱ��������
    while (1)
    {
        n = getch();
        //��Ϸ�з�ֹ����������
        if(n != UP && n != DOWN && n != RIGHT && n != LEFT && n != SPACE && n != ESC)
        {
            n = tmp;
        }
        switch (n)
        {
        case UP: //���������ϼ�ʱ
            if (tmp != DOWN) //�������ƶ��ķ���������ʱ���ܸı��ߵķ��򣬼���ֹ�߳��֡�ԭ�ص�ͷ��
            {
                AutoMove(0, -1); //�����ƶ�
                tmp = UP; //��¼��ǰ�ߵ��ƶ�����
            }
            else
            {
                n = tmp; //��������Ч�������������ƶ�
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
            system("pause>nul"); //��ͣ�����������
            break;
        case ESC:
            system("cls"); //�����Ļ��������Ϸ��������
            color(112);
            JumpTo(LIE - 6 , HANG / 2);
            printf("�� Ϸ �� �� ��\a");
            JumpTo(0, HANG - 1);
            exit(0);
        }
    }
}

void AfterGame(int x, int y)
{
    //����ͷ���������λ����ʳ��������ȼ�һ���÷ּ�һ���������һ��ʳ��
    if (maps[head.y + y][head.x + x] == FOOD)
    {
        head.lenth++; //�����ȼ�һ
        grade += 1; //�÷ּ�һ��ʵʱ����
        color(112);
        JumpTo(2 , HANG);
        printf("��ǰ�÷�:%d��", grade);
        InitFood(); //�������ʳ��
    }
    //����ͷ���������λ����ǽ������������Ϸ����
    else if (maps[head.y + y][head.x + x] == WALL || maps[head.y + y][head.x + x] == BODY)
    {
        system("cls");
        color(112);
        JumpTo(LIE - 6 , 6);
        printf("�� Ϸ �� �� ��\a"); //��һ�����������
        JumpTo(2 * LIE - 24 , HANG - 1);
        printf("���ߣ�r");
        JumpTo(LIE - 18 , HANG / 2);
        if (grade > best)
        {
            printf(" ���Ѿ�ˢ������߼�¼�����ķ�����%d��", grade);
            WriteGrade();
        }
        else if(grade == best)
        {
            printf(" ���Ѿ�׷ƽ����߼�¼�����ķ�����%d��", grade);
        }
        else
        {
            printf(" ���ķ�����%d�֣�����%d�ֲ���׷ƽ��¼", grade , best - grade);
        }
        int n; //��ȡ��ֵ��������һ�ֻ����˳���Ϸ
        while (1)
        {
            JumpTo(LIE - 20 , HANG - 6);
            printf("���¿�ʼ��Ϸ�밴ENTER��...�˳���Ϸ�밴ESC��...");
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
                printf("\a"); //��һ�����������
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
