// 贪吃蛇.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"snake.h"
#include<Windows.h>
#include<conio.h>
#include<iostream>
using namespace std;

int main()
{
	snake shanke;
	system("cls");
	cout << "**********Snake*********" << endl;
	cout << "*********任意键开始*********" << endl;
	cout << "*********退出按：q*********" << endl;
	char quit = _getch();
	if (quit == 'q')
		return 1;
	else
        shanke.game();
        return 0;
}

