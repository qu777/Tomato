// 99乘法表.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iomanip>
#include<windows.h>
#include<iostream>
using namespace std;

void SetPos(int i, int j)//设定光标位置
{
	COORD pos = { i - 1,j - 1 };//坐标变量
	HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);//获取输出句柄
	SetConsoleCursorPosition(Out, pos);//设定光标位置
}

int main()
{
	int i, j;
	for (i = 1; i <= 9; i++)
	{
		for (j = 1; j <= i; j++)
		{
			if (j == 3 && i == 3|| j == 3 && i == 4)
			{
				cout << " ";
			}
			cout << setw(5);
			cout <<j<<"*"<<i<<"="<< j*i;
		}
		cout << endl;
	}
	return 0;
}
