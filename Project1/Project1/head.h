#pragma once
#define DEF_SNAKE_LONG 20

char g_strGameBack[20][48] = { "███████████████████████\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"█                                          █\n",
"███████████████████████" };

//蛇数组
int g_arrSnake[DEF_SNAKE_LONG][3] = { 0 };
//方向
enum {to_east = 2,to_west = -2,to_north = -1,to_south = 1};
//蛇长度
int g_nSnakelen = 2;//记录尾结点下标
//蛇方向
int g_nSnakeDir = to_west;//全局变量默认初始化0
//是否产生新食物
bool g_bIsProFood = true;
//产生随机坐标
int g_nRow ;
int g_nColumn ;
//分数
int g_nScore = 0;