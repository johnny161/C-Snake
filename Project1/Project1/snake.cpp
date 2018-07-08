#include<stdio.h>
#include<stdlib.h>
#include"head.h"
#include<time.h>
#include<conio.h>
#include<string.h>
#include"resource.h"
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma warning(disable:4996)

//播放音乐
void MyPlaySound();
//显示首页
void FirstPage();
//按空格键
void TestSpace();
//停止播放
void MyStopMusic();
//画背景
void ShowBackground();
//为蛇产生一个随机的位置
void SetSnakeRandPos();
//画蛇
void DrawSnake();
//蛇动
void SnakeMove();
//销毁蛇
void Destroy();
//蛇随方向动起来
void ChangeDir();
//蛇死亡判断
bool IsSnakeDie();
//产生新的食物
void ProduceFood();
//蛇变长
void SnakeGroupUp();
//计分
void Score();

int main() 
{
	//播放音乐
	MyPlaySound();
	//显示首页
	FirstPage();
	//按空格键
	TestSpace();
	//停止播放
	MyStopMusic();
	//清空
	system("cls");
	//游戏界面
 	SetSnakeRandPos();
	//画背景
	ShowBackground();

	//游戏界面
	while (1)
	{
		system("cls");
		//产生食物
		ProduceFood();
		//蛇变长
		SnakeGroupUp();
		//改变方向
		ChangeDir();
		//判断死亡
		if (false == IsSnakeDie())
		{
			printf("\nSnake die\n");
			break;
		}
		//蛇动
		SnakeMove();
		//显示背景
		ShowBackground();
		//显示分数
		Score();
		Sleep(500);
	}

	system("pause");
	return 0;
}
void Score()
{
	COORD rd;
	rd.X = 55;
	rd.Y = 8;
	//设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//打印
	printf("分数");
	rd.X = 56;
	rd.Y = 9;
	//设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//打印
	printf("%d",g_nScore);
}

//蛇变长
void SnakeGroupUp()
{
	//蛇头坐标跟食物坐标相等
	if (g_nRow == g_arrSnake[0][0] && g_nColumn*2 == g_arrSnake[0][1])
	{
		//蛇长大
		if (to_east == g_arrSnake[g_nSnakelen][2])
		{
			g_arrSnake[g_nSnakelen + 1][0] = g_arrSnake[g_nSnakelen][0];
			g_arrSnake[g_nSnakelen + 1][1] = g_arrSnake[g_nSnakelen][1] - 2;
			g_arrSnake[g_nSnakelen + 1][2] = g_arrSnake[g_nSnakelen][2];
		}
		else if (to_west == g_arrSnake[g_nSnakelen][2])
		{
			g_arrSnake[g_nSnakelen + 1][0] = g_arrSnake[g_nSnakelen][0];
			g_arrSnake[g_nSnakelen + 1][1] = g_arrSnake[g_nSnakelen][1] + 2;
			g_arrSnake[g_nSnakelen + 1][2] = g_arrSnake[g_nSnakelen][2];
		}
		else if (to_north == g_arrSnake[g_nSnakelen][2])
		{
			g_arrSnake[g_nSnakelen + 1][0] = g_arrSnake[g_nSnakelen][0] + 1;
			g_arrSnake[g_nSnakelen + 1][1] = g_arrSnake[g_nSnakelen][1];
			g_arrSnake[g_nSnakelen + 1][2] = g_arrSnake[g_nSnakelen][2];
		}
		else if (to_south == g_arrSnake[g_nSnakelen][2])
		{
			g_arrSnake[g_nSnakelen + 1][0] = g_arrSnake[g_nSnakelen][0] - 1;
			g_arrSnake[g_nSnakelen + 1][1] = g_arrSnake[g_nSnakelen][1];
			g_arrSnake[g_nSnakelen + 1][2] = g_arrSnake[g_nSnakelen][2];
		}
		g_nSnakelen++;
		g_bIsProFood = true;
		g_nScore++;
	}
}

//产生新的食物
void ProduceFood()
{
	//判断是否产生新的食物
	if (false == g_bIsProFood)//否
	{
		return;
	}

	srand((unsigned int)time(NULL));

	while (1)
	{
		bool bFlag = true;

		g_nRow = rand() % 18 + 1;
		g_nColumn = rand() % 21 + 1;

		for (int i = 0; g_arrSnake[i][0] != 0; i++)
		{
			if (g_nRow == g_arrSnake[i][0] && g_nColumn == g_arrSnake[i][1])
			{
				bFlag = false;
			}
		}
		if (true == bFlag)
		{
			break;
		}
	}
	
	//坐标画食物
	strncpy(&g_strGameBack[g_nRow][g_nColumn * 2], "★", 2);
	g_bIsProFood = false;
}

//蛇死亡判断
bool IsSnakeDie()
{
	if (to_west == g_arrSnake[0][2] || to_east == g_arrSnake[0][2])
	{
		if (0 == strncmp(&g_strGameBack[g_arrSnake[0][0]][g_arrSnake[0][1] + g_arrSnake[0][2]], "█", 2))
		{
			return false;
		}
	}
	else
	{
		if (0 == strncmp(&g_strGameBack[g_arrSnake[0][0] + g_arrSnake[0][2]][g_arrSnake[0][1]], "█", 2))
		{
			return false;
		}
	}
	return true;
}

//蛇随方向动起来
void ChangeDir()
{
	if (GetAsyncKeyState('W'))
	{
		if (to_south != g_arrSnake[0][2])
		{
			g_nSnakeDir = to_north;
		}
	}
	else if (GetAsyncKeyState('S'))
	{
		if (to_north != g_arrSnake[0][2])
		{
			g_nSnakeDir = to_south;
		}
	}
	else if (GetAsyncKeyState('A'))
	{
		if (to_east != g_arrSnake[0][2])
		{
			g_nSnakeDir = to_west;
		}
	}
	else if (GetAsyncKeyState('D'))
	{
		if (to_west != g_arrSnake[0][2])
		{
			g_nSnakeDir = to_east;
		}
	}
	g_arrSnake[0][2] = g_nSnakeDir;
}

//销毁蛇
void Destroy()
{
	for (int i = 0; g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_strGameBack[g_arrSnake[i][0]][g_arrSnake[i][1]], "  ", 2);
	}
}

//蛇动
void SnakeMove()
{
	int i = DEF_SNAKE_LONG - 1;
	//销毁蛇
	Destroy();
	for (i; i >= 1; i--)
	{
		//过滤非法蛇
		if (0 == g_arrSnake[i][0])
		{
			continue;
		}
		//把前一个节点的值赋值给当前节点
		g_arrSnake[i][0] = g_arrSnake[i - 1][0];
		g_arrSnake[i][1] = g_arrSnake[i - 1][1];
		g_arrSnake[i][2] = g_arrSnake[i - 1][2];
	}
	//处理蛇头

	if (to_west == g_arrSnake[0][2] || to_east == g_arrSnake[0][2])
	{
		g_arrSnake[0][1] += g_arrSnake[0][2];
	}
	else
	{
		g_arrSnake[0][0] += g_arrSnake[0][2];
	}
	//画蛇
	DrawSnake();
}

//为蛇产生一个随机的位置
void SetSnakeRandPos()
{
	int nX = -1;
	int nY = -1;

	//产生随机数
	srand((unsigned int)time(NULL));//种种子
	nX = rand() % 19 + 1;//1-19格（右边保留三格蛇长）
	nY = rand() % 18 + 1;

	//初始化蛇的三个结点
	g_arrSnake[0][0] = nY;//行
	g_arrSnake[0][1] = nX*2;
	g_arrSnake[0][2] = to_west;

	g_arrSnake[1][0] = nY;//行
	g_arrSnake[1][1] = nX * 2 + 2;
	g_arrSnake[1][2] = to_west;

	g_arrSnake[2][0] = nY;//行
	g_arrSnake[2][1] = nX * 2 + 4;
	g_arrSnake[2][2] = to_west;

	//画到背景上
	DrawSnake();
}

//画蛇
void DrawSnake()
{
	for (int i = 0; g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_strGameBack[g_arrSnake[i][0]][g_arrSnake[i][1]],"█",2);
	}
}

//画背景
void ShowBackground()
{
	for (int i = 0; i < 20; i++)
	{
		printf(g_strGameBack[i]);
	}
}

//显示首页
void FirstPage()
{
	printf("\n\n\n\n");
	printf("\t\t\t <<欢迎进入贪吃蛇世界>>\n");
	printf("\t\t\t <<按空格开始游戏>>\n");
	printf("\t\t\t<<w a s d 控制蛇的方向>>\n");
}

//播放音乐
void MyPlaySound()
{
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
	//PlaySound("10+往事只能回味.wav", NULL, SND_FILENAME | SND_ASYNC);
}

//测试空格键
void TestSpace()
{
	char chInput;
	while (1)
	{
		chInput = _getch();
		if (' ' == chInput)
		{
			break;
		}

	}
}

//停止播放
void MyStopMusic()
{
	PlaySound(NULL, 0, 0);
}