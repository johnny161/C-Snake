#pragma once
#define DEF_SNAKE_LONG 20

char g_strGameBack[20][48] = { "����������������������������������������������\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"��                                          ��\n",
"����������������������������������������������" };

//������
int g_arrSnake[DEF_SNAKE_LONG][3] = { 0 };
//����
enum {to_east = 2,to_west = -2,to_north = -1,to_south = 1};
//�߳���
int g_nSnakelen = 2;//��¼β����±�
//�߷���
int g_nSnakeDir = to_west;//ȫ�ֱ���Ĭ�ϳ�ʼ��0
//�Ƿ������ʳ��
bool g_bIsProFood = true;
//�����������
int g_nRow ;
int g_nColumn ;
//����
int g_nScore = 0;