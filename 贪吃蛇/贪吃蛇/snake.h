#pragma once
struct boby//蛇身（链表结构)
{
	int x, y;
	boby * next;
};
class snake
{
private:
	boby * head;//蛇头
	int count;//
	int speed;//
	int director;//移动方向
	int exist;//判断食物是否存在
	int food_x;//食物x坐标
	int food_y;//食物y坐标
public:
	snake(int a = 3, int b = 4, int c = 1, int d = 0);
	void edge();
	void print();
	void food();
	void eat();
	int over();
	void game();
	void move();
	void setpos(int , int );

};