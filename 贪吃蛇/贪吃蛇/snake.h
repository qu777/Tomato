#pragma once
struct boby//��������ṹ)
{
	int x, y;
	boby * next;
};
class snake
{
private:
	boby * head;//��ͷ
	int count;//
	int speed;//
	int director;//�ƶ�����
	int exist;//�ж�ʳ���Ƿ����
	int food_x;//ʳ��x����
	int food_y;//ʳ��y����
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