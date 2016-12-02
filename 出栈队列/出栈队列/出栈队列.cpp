// ��ջ����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <stack>  
#include<vector>
#include<string>
using namespace std;

vector<string> slove;

bool IsStackPopOrder(int *pushorder, int *poporder, int len)
{
	bool isorder = false;
	if (pushorder != NULL && poporder != NULL && len > 0)
	{
		stack<int> s;
		//��ջ
		int *pnextpush = pushorder;
		//��ջ
		int *pnextpop = poporder;
		//ѭ��ֱ������Ԫ�ض��ѳ�ջ
		while ((pnextpop - poporder) < len)
		{
			//��ջֱ����ǰԪ�����ջԪ����ͬ
			while (s.empty() || s.top() != *pnextpop)
			{
				if ((pnextpush - pushorder) == len)
				{
					break;
				}
				s.push(*pnextpush);
				slove.push_back("in");
				pnextpush++;
			}

			if (s.top() == *pnextpop)
			{
				s.pop();
				slove.push_back("out");
				pnextpop++;
			}
			else
			{
				break;
			}

		}
		if ((pnextpop - poporder) == len && s.empty())
			isorder = true;
	}
	return isorder;
}
void main()
{
	int array1[7] = { 1, 2, 3, 4, 5, 6, 7 };
	int array2[7] = { 4, 3, 2, 1, 7, 6, 5 };
	if (IsStackPopOrder(array1, array2, 7))
	{
		cout << "��" << endl;
		vector<string>::iterator a = slove.begin();
		while (a != slove.end())
		{
			cout << *a << endl;
			a++;
		}
	}
	else
		cout << "��" << endl;
}
