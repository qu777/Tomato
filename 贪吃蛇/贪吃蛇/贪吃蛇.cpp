// ̰����.cpp : �������̨Ӧ�ó������ڵ㡣
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
	cout << "*********�������ʼ*********" << endl;
	cout << "*********�˳�����q*********" << endl;
	char quit = _getch();
	if (quit == 'q')
		return 1;
	else
        shanke.game();
        return 0;
}

