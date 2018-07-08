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

//��������
void MyPlaySound();
//��ʾ��ҳ
void FirstPage();
//���ո��
void TestSpace();
//ֹͣ����
void MyStopMusic();
//������
void ShowBackground();
//Ϊ�߲���һ�������λ��
void SetSnakeRandPos();
//����
void DrawSnake();
//�߶�
void SnakeMove();
//������
void Destroy();
//���淽������
void ChangeDir();
//�������ж�
bool IsSnakeDie();
//�����µ�ʳ��
void ProduceFood();
//�߱䳤
void SnakeGroupUp();
//�Ʒ�
void Score();

int main() 
{
	//��������
	MyPlaySound();
	//��ʾ��ҳ
	FirstPage();
	//���ո��
	TestSpace();
	//ֹͣ����
	MyStopMusic();
	//���
	system("cls");
	//��Ϸ����
 	SetSnakeRandPos();
	//������
	ShowBackground();

	//��Ϸ����
	while (1)
	{
		system("cls");
		//����ʳ��
		ProduceFood();
		//�߱䳤
		SnakeGroupUp();
		//�ı䷽��
		ChangeDir();
		//�ж�����
		if (false == IsSnakeDie())
		{
			printf("\nSnake die\n");
			break;
		}
		//�߶�
		SnakeMove();
		//��ʾ����
		ShowBackground();
		//��ʾ����
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
	//���ù��λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//��ӡ
	printf("����");
	rd.X = 56;
	rd.Y = 9;
	//���ù��λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//��ӡ
	printf("%d",g_nScore);
}

//�߱䳤
void SnakeGroupUp()
{
	//��ͷ�����ʳ���������
	if (g_nRow == g_arrSnake[0][0] && g_nColumn*2 == g_arrSnake[0][1])
	{
		//�߳���
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

//�����µ�ʳ��
void ProduceFood()
{
	//�ж��Ƿ�����µ�ʳ��
	if (false == g_bIsProFood)//��
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
	
	//���껭ʳ��
	strncpy(&g_strGameBack[g_nRow][g_nColumn * 2], "��", 2);
	g_bIsProFood = false;
}

//�������ж�
bool IsSnakeDie()
{
	if (to_west == g_arrSnake[0][2] || to_east == g_arrSnake[0][2])
	{
		if (0 == strncmp(&g_strGameBack[g_arrSnake[0][0]][g_arrSnake[0][1] + g_arrSnake[0][2]], "��", 2))
		{
			return false;
		}
	}
	else
	{
		if (0 == strncmp(&g_strGameBack[g_arrSnake[0][0] + g_arrSnake[0][2]][g_arrSnake[0][1]], "��", 2))
		{
			return false;
		}
	}
	return true;
}

//���淽������
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

//������
void Destroy()
{
	for (int i = 0; g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_strGameBack[g_arrSnake[i][0]][g_arrSnake[i][1]], "  ", 2);
	}
}

//�߶�
void SnakeMove()
{
	int i = DEF_SNAKE_LONG - 1;
	//������
	Destroy();
	for (i; i >= 1; i--)
	{
		//���˷Ƿ���
		if (0 == g_arrSnake[i][0])
		{
			continue;
		}
		//��ǰһ���ڵ��ֵ��ֵ����ǰ�ڵ�
		g_arrSnake[i][0] = g_arrSnake[i - 1][0];
		g_arrSnake[i][1] = g_arrSnake[i - 1][1];
		g_arrSnake[i][2] = g_arrSnake[i - 1][2];
	}
	//������ͷ

	if (to_west == g_arrSnake[0][2] || to_east == g_arrSnake[0][2])
	{
		g_arrSnake[0][1] += g_arrSnake[0][2];
	}
	else
	{
		g_arrSnake[0][0] += g_arrSnake[0][2];
	}
	//����
	DrawSnake();
}

//Ϊ�߲���һ�������λ��
void SetSnakeRandPos()
{
	int nX = -1;
	int nY = -1;

	//���������
	srand((unsigned int)time(NULL));//������
	nX = rand() % 19 + 1;//1-19���ұ߱��������߳���
	nY = rand() % 18 + 1;

	//��ʼ���ߵ��������
	g_arrSnake[0][0] = nY;//��
	g_arrSnake[0][1] = nX*2;
	g_arrSnake[0][2] = to_west;

	g_arrSnake[1][0] = nY;//��
	g_arrSnake[1][1] = nX * 2 + 2;
	g_arrSnake[1][2] = to_west;

	g_arrSnake[2][0] = nY;//��
	g_arrSnake[2][1] = nX * 2 + 4;
	g_arrSnake[2][2] = to_west;

	//����������
	DrawSnake();
}

//����
void DrawSnake()
{
	for (int i = 0; g_arrSnake[i][0] != 0; i++)
	{
		strncpy(&g_strGameBack[g_arrSnake[i][0]][g_arrSnake[i][1]],"��",2);
	}
}

//������
void ShowBackground()
{
	for (int i = 0; i < 20; i++)
	{
		printf(g_strGameBack[i]);
	}
}

//��ʾ��ҳ
void FirstPage()
{
	printf("\n\n\n\n");
	printf("\t\t\t <<��ӭ����̰��������>>\n");
	printf("\t\t\t <<���ո�ʼ��Ϸ>>\n");
	printf("\t\t\t<<w a s d �����ߵķ���>>\n");
}

//��������
void MyPlaySound()
{
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
	//PlaySound("10+����ֻ�ܻ�ζ.wav", NULL, SND_FILENAME | SND_ASYNC);
}

//���Կո��
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

//ֹͣ����
void MyStopMusic()
{
	PlaySound(NULL, 0, 0);
}