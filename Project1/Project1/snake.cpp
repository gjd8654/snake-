/*
1.数据的分析
2.过程的分析
3.主函数
*/
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
//#include<Windows.h>
#include<graphics.h>//创建窗口
#include<conio.h>//获取键盘键码
#include<time.h>//随机函数
//坐标属性
typedef struct pointXY
{
	int x;
	int y;
}MYPOINT;
//蛇的属性
struct Snake
{
	int num;
	MYPOINT xy[100];
	char postion;
}snake;
//食物的属性
struct Food
{
	MYPOINT fdxy;//食物的坐标
	int eatgrade;//吃了食物有多少分
	int flag;//食物是否存在
}food;
HWND hwnd = NULL;//表示主窗口
//方向枚举出来
//小键盘，键码值
enum movPostion { right = 77, left = 75, down = 80, up = 72 };
//初始化蛇
void initSnake();
//画蛇
void drawSnake();
//移动蛇
void moveSnake();
//按键处理
void keyDown();
//初始化食物
void initFood();
//画食物
void drawFood();
//吃食物
void eatFood();
//蛇挂掉
int snakeDie();
//显示分数
void showGrade();
void pauseMoment();

//void BeginBatchDraw();
//void EndBatchDraw();
int main()
{
	srand((unsigned int)time(NULL));//随机函数
	hwnd = initgraph(640, 480);//initgraph()创建窗口函数,easyx.h
	setbkcolor(WHITE);//背景颜色
	initSnake();
	while (1)
	{
		BeginBatchDraw();//防止闪屏,easyx.h
		cleardevice();//如果颜色没变，刷新一下
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
		moveSnake();//放后面,防止食物出现在第一个闪一下
		while (_kbhit())//conio.h
		{
			pauseMoment();
			keyDown();
		}
		Sleep(100);//防止太快,synchapi.h
		FlushBatchDraw();//防止闪屏,easyx.h
	}
	int n = getchar();//防止闪屏
	closegraph();//关闭图形绘制窗口
	EndBatchDraw();//防止闪屏,easyx.h
	return 0;
}
void initSnake()
{
	//写出前三节的属性
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
		setlinecolor(BLACK);//矩形边框颜色
		setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
		//画矩形
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);
	}
}
void moveSnake()
{
	//除了第一节
	for (int i = snake.num - 1; i > 0; i--)
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	//第一节
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
	userKey = _getch();//<conin.h>，按下任意键
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
	food.fdxy.y = rand() % 48 * 10;//防止蛇吃不到食物
	food.flag = 1;//食物存在
	for (int i = 0; i > snake.num; i++)
	{
		if (food.fdxy.x == snake.xy[i].x && food.fdxy.y == snake.xy[i].y)
		{
			//如果食物坐标和蛇坐标重合，重新产生
			food.fdxy.x = rand() % 65 * 10;
			food.fdxy.y = rand() % 48 * 10;
		}
	}
}
void drawFood()
{
	setlinecolor(BLACK);//矩形边框颜色
	setfillcolor(RED);//填充颜色
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x + 10, food.fdxy.y + 10);//填充范围
}
void eatFood()
{
	//蛇变长
	//食物重新生成
	//分数增加
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
		outtextxy(200, 200, "你撞南墙了！");
		MessageBox(hwnd, "GameOver!", "撞墙警告", MB_OK);//WinUser.h,弹出一个小窗口
		return 1;//返回1表示游戏结束
	}
	//吃自己
	for (int i = 1; i < snake.num; i++)
	{
		if (snake.xy[0].x == snake.xy[i].x && snake.xy[0].y == snake.xy[i].y)
		{
			outtextxy(200, 200, "你撞自己了！");
			MessageBox(hwnd, "GameOver!", "自杀警告", MB_OK);
			return 1;//返回1表示游戏结束
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
	outtextxy(580 - 20, 20, "分数：");
	outtextxy(580 + 50 - 20, 20, grade);
}
void pauseMoment()
{
	if (_getch() == 32)
	{
		while (_getch() != 32);//停在这里
	}
}