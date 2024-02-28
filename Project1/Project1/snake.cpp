/*
1.���ݵķ���
2.���̵ķ���
3.������
*/
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
//#include<Windows.h>
#include<graphics.h>//��������
#include<conio.h>//��ȡ���̼���
#include<time.h>//�������
//��������
typedef struct pointXY
{
	int x;
	int y;
}MYPOINT;
//�ߵ�����
struct Snake
{
	int num;
	MYPOINT xy[100];
	char postion;
}snake;
//ʳ�������
struct Food
{
	MYPOINT fdxy;//ʳ�������
	int eatgrade;//����ʳ���ж��ٷ�
	int flag;//ʳ���Ƿ����
}food;
HWND hwnd = NULL;//��ʾ������
//����ö�ٳ���
//С���̣�����ֵ
enum movPostion { right = 77, left = 75, down = 80, up = 72 };
//��ʼ����
void initSnake();
//����
void drawSnake();
//�ƶ���
void moveSnake();
//��������
void keyDown();
//��ʼ��ʳ��
void initFood();
//��ʳ��
void drawFood();
//��ʳ��
void eatFood();
//�߹ҵ�
int snakeDie();
//��ʾ����
void showGrade();
void pauseMoment();

//void BeginBatchDraw();
//void EndBatchDraw();
int main()
{
	srand((unsigned int)time(NULL));//�������
	hwnd = initgraph(640, 480);//initgraph()�������ں���,easyx.h
	setbkcolor(WHITE);//������ɫ
	initSnake();
	while (1)
	{
		BeginBatchDraw();//��ֹ����,easyx.h
		cleardevice();//�����ɫû�䣬ˢ��һ��
		if (food.flag == 0)
		{
			initFood();
		}
		drawFood();
		drawSnake();
		if (snakeDie())
		{
			break;
		}
		eatFood();
		showGrade();
		moveSnake();//�ź���,��ֹʳ������ڵ�һ����һ��
		while (_kbhit())//conio.h
		{
			pauseMoment();
			keyDown();
		}
		Sleep(100);//��ֹ̫��,synchapi.h
		FlushBatchDraw();//��ֹ����,easyx.h
	}
	int n = getchar();//��ֹ����
	closegraph();//�ر�ͼ�λ��ƴ���
	EndBatchDraw();//��ֹ����,easyx.h
	return 0;
}
void initSnake()
{
	//д��ǰ���ڵ�����
	snake.xy[2].x = 0;
	snake.xy[2].y = 0;

	snake.xy[1].x = 10;
	snake.xy[1].y = 0;

	snake.xy[0].x = 20;
	snake.xy[0].y = 0;

	snake.num = 3;
	snake.postion = right;

	food.flag = 0;
	food.eatgrade = 0;
}
void drawSnake()
{
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(BLACK);//���α߿���ɫ
		setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
		//������
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
	}
}
void moveSnake()
{
	//���˵�һ��
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	//��һ��
	switch (snake.postion)
	{
	case right:
		snake.xy[0].x += 10;
		break;
	case left:
		snake.xy[0].x -= 10;
		break;
	case down:
		snake.xy[0].y += 10;
		break;
	case up:
		snake.xy[0].y -= 10;
		break;
	default:
		break;
	}

}
void keyDown()
{
	char userKey = 0;
	userKey = _getch();//<conin.h>�����������
	switch (userKey)
	{
	case right:
		if (snake.postion != left)
			snake.postion = right;
		break;
	case left:
		if (snake.postion != right)
			snake.postion = left;
		break;
	case down:
		if (snake.postion != up)
			snake.postion = down;
		break;
	case up:
		if (snake.postion != down)
			snake.postion = up;
		break;
	default:
		break;
	}
}
void initFood()
{
	food.fdxy.x = rand() % 65 * 10;
	food.fdxy.y = rand() % 48 * 10;//��ֹ�߳Բ���ʳ��
	food.flag = 1;//ʳ�����
	for (int i = 0; i > snake.num; i++)
	{
		if (food.fdxy.x == snake.xy[i].x && food.fdxy.y == snake.xy[i].y)
		{
			//���ʳ��������������غϣ����²���
			food.fdxy.x = rand() % 65 * 10;
			food.fdxy.y = rand() % 48 * 10;
		}
	}
}
void drawFood()
{
	setlinecolor(BLACK);//���α߿���ɫ
	setfillcolor(RED);//�����ɫ
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x + 10, food.fdxy.y + 10);//��䷶Χ
}
void eatFood()
{
	//�߱䳤
	//ʳ����������
	//��������
	if (snake.xy[0].x == food.fdxy.x && snake.xy[0].y == food.fdxy.y)
	{
		snake.num++;
		food.eatgrade += 10;
		food.flag = 0;
	}
}
int snakeDie()
{
	if (snake.xy[0].x > 640 || snake.xy[0].x < 0 || snake.xy[0].y > 480 || snake.xy[0].y < 0)
	{
		outtextxy(200, 200, "��ײ��ǽ�ˣ�");
		MessageBox(hwnd, "GameOver!", "ײǽ����", MB_OK);//WinUser.h,����һ��С����
		return 1;//����1��ʾ��Ϸ����
	}
	//���Լ�
	for (int i = 1; i < snake.num; i++)
	{
		if (snake.xy[0].x == snake.xy[i].x && snake.xy[0].y == snake.xy[i].y)
		{
			outtextxy(200, 200, "��ײ�Լ��ˣ�");
			MessageBox(hwnd, "GameOver!", "��ɱ����", MB_OK);
			return 1;//����1��ʾ��Ϸ����
		}
	}
	return 0;
}
void showGrade()
{
	char grade[100] = "";
	sprintf(grade, "%d", food.eatgrade);
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTBLUE);
	outtextxy(580 - 20, 20, "������");
	outtextxy(580 + 50 - 20, 20, grade);
}
void pauseMoment()
{
	if (_getch() == 32)
	{
		while (_getch() != 32);//ͣ������
	}
}