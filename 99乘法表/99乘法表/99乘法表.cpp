// 99�˷���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iomanip>
#include<windows.h>
#include<iostream>
using namespace std;

void SetPos(int i, int j)//�趨���λ��
{
	COORD pos = { i - 1,j - 1 };//�������
	HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ������
	SetConsoleCursorPosition(Out, pos);//�趨���λ��
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
