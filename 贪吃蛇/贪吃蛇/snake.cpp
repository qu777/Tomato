#include"stdafx.h"
#include"snake.h"
#include<windows.h>
#include<iostream>
#include<ctime>
#include<conio.h>

using namespace std;

void snake::setpos(int i, int j)//设置光标的位置
{
	COORD pos = { i - 1,j - 1 };
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(out, &cursor_info);
	SetConsoleCursorPosition(out, pos);
}

snake::snake(int a, int b, int c, int d)//构造函数
{
	exist = d;//开始没有食物
	boby *temp1, *temp2;
	head = new boby;
	head->x = 5;
	head->y = 2;

	temp1 = new boby;
	temp1->x = 4;
	temp1->y = 2;

	temp2 = new boby;
	temp2->x = 3;
	temp2->y = 2;

	head->next = temp1;
	temp1->next = temp2;
	temp2->next = nullptr;

	director = b;
	count = a;
	speed = c;
}

void snake::edge()//设置边界，结束条件
{
	int i;
	for (i = 1; i <= 77; i++)
	{
		setpos(i, 1);
		cout << "*";
		setpos(i, 29);
		cout << "*";
	}
	for (i = 2; i <= 28; i++)
	{
		setpos(1, i);
		cout << "*";
		setpos(77, i);
		cout << "*";
	}
	setpos(80, 3);
	cout << "Snake";
	setpos(80, 5);
	cout << "count:" << count;
	setpos(80, 7);
	cout << "Level:" << speed;
}
void snake::food()//产生食物
{
	boby *p;
	int inboby = 0;
	srand((unsigned)time(NULL));
	while (1)
	{
		
		food_x = rand() % 74 + 2;
		food_y = rand() % 26 + 2;
		p = head;
		while (p != nullptr)//判断食物是不是在蛇身
		{
			if (p->x == food_x && p->y == food_y)
			{
				inboby = 1;
				break;
			}
			p = p->next;
		}
		if (inboby == 0)//若不在生成成功
			break;
		else
			inboby = 0;
	}
}



int snake::over()//游戏结束
{
	boby * p;
	p = head;
	if ((head->x) >= 77 || (head->x) <= 1 || (head->y) <= 1 || (head->y) >= 29)//判断是不是超出边界
		return 1;
	p = head->next;
	while (p != nullptr)//判断是不是撞蛇身
	{
		if ((head->x == p->x) && (head->y == p->y))
			return 1;
		p = p->next;
	}
	return 0;
}

void snake::print()//形成蛇
{
	boby *p;
	setpos(head->x, head->y);
	cout << "@" << endl;
	p = head->next;
	while (p != nullptr)
	{
		setpos(p->x, p->y);
		cout << "*";
		p = p->next;
	}
	setpos(food_x, food_y);
	cout << "$";
}

void snake::move()//移动蛇
{
	boby *temp;
	temp = new(boby);
	if (director == 1)
	{
		temp->x = head->x;
		temp->y = head->y - 1;
		temp->next = head;
		head = temp;
	}
	if (director == 2)
	{
		temp->x = head->x;
		temp->y = head->y + 1;
		temp->next = head;
		head = temp;
	}
	if (director == 3)
	{
		temp->x = head->x-1;
		temp->y = head->y;
		temp->next = head;
		head = temp;
	}
	if (director == 4)
	{
		temp->x = head->x+1;
		temp->y = head->y;
		temp->next = head;
		head = temp;
	}
}

void snake::eat()//吃食物
{
	if (head->x == food_x && head->y == food_y)
	{
		exist = 0;
		count++;
		setpos(80, 5);
		cout << "length:" << count;
		if (count % 20 == 0)
		{
			speed++;
			setpos(80, 7);
			cout << "level:" << speed;
		}	
	}
}

void snake::game()//游戏执行
{
	system("cls");//刷新屏幕
	char x;
	boby *p;
	edge();
	print();
	while (1)
	{
		if (_kbhit())//判断键盘是否有操作
		{
			x = _getch();//读入缓冲区值赋给x
			if (x == -32)
			{
				x = _getch();
			}
			if ((x == 'w' || x == 'W' || x=='8' || x==72) && director != 2)//方向不能与输入的相反,wasd,上下左右箭头，2468都可操作
				director = 1;
			if ((x == 's' || x == 'S' || x=='2' || x==80) && director != 1)
				director = 2;
			if ((x == 'a' || x == 'A' || x=='4' || x==75) && director != 4)
				director = 3;
			if ((x == 'd' || x == 'D' || x=='6' || x==77) && director != 3)
				director = 4;
			while (_kbhit())//读取之后的所有操作
				_getch();
		}
		if (exist == 0)//产生食物
		{
			food();
			exist = 1;
		}
		move();//移动蛇
		eat();//吃食物
		if (speed == 10)
			break;
		print();
		if (exist == 1)//若没有吃到食物，删除蛇尾
		{
			p = head;
			while (p->next->next != nullptr)
				p = p->next;
			setpos(p->next->x, p->next->y);
			cout << " ";
			delete (p->next);
			p->next = nullptr;
		}
		if (over())
			break;
		Sleep(500 - speed * 50);//根据等级设置蛇身移动的快慢
	}
	system("cls");
	if (speed == 10)
	{
		setpos(30, 25);
		cout << "oh,my gad!" << endl;
		system("pause");
	}
	else
	{
		setpos(30, 10);
		cout << "you lose,the length is " << count << endl;
		system("pause");
	}
}
