#pragma once
#include"stdafx.h"
#include"Gmap.h"
#include<iostream>
#include<ctime>

const int PLAYERSPEED = 6;//����ٶ�
const int ENERMYSPEED = 4;//�����ٶ�
const int LEGCOUNTS = 5;//�����ȵ�����
const int DISTANCE = 10;//ͼ�η�Χ
const int BLUE_ALERT = 8;//��ɫ���䷶Χ
const int D_OFFSET = 2;//��ͼ���
const int RD = (DISTANCE + D_OFFSET);

enum TWARDS { UP, DOWN, LEFT, RIGHT, OVER };//����ö��

class Gobject//������
{
protected:
	int mX;
	int mY;
	TWARDS twCommand;//ָ���
	POINT point;//��������
	int dRow;//�߼�������
	int dArray;//�߼�������
	int speed;//�ٶ�
	TWARDS tw;//����
	int frame;//֡��
	bool Achive();//�ж������Ƿ񵽴��߼�����
	bool Collision();//�߼���ײ��⣬������ڷ��ں����λ��
	int PtTransform(int k);//��ʵ������ת��Ϊ�߼�����
	virtual void AchiveCtrl();//�����߼�����������
public:
	void SetPosition(int Row, int Array);
	void DrawBlank(HDC & hdc);
	void virtual Draw(HDC & kdc) = 0;//���ƶ���
	static Gmap * pStage;//ָ���ͼ���ָ�룬����Ϊ��̬��ʹ�������������ʹ����ͬ�ĵ�ͼ
	Gobject(int Row, int Array)
	{
		frame = 1;
		pStage = NULL;
		this->dRow = Row;
		this->dArray = Array;
		this->point.y = dRow*pStage->LD + pStage->LD / 2;
		this->point.x = dArray*pStage->LD + pStage->LD / 2;
		this->mX = point.x;
		this->mY = point.y;
	}
	void virtual action() = 0;//���ݱ���ı���
	int GetRow();
	int GetArray();
};



class PacMan :public Gobject//��ҿ��ƵĶ���
{
protected:
	virtual void AchiveCtrl();//��д�麯��
public:
	POINT GetPos();
	TWARDS GetTw();
	bool Win();
	void Draw(HDC & hdc);
	void SetTwCommand(TWARDS command);
	void Over();
	PacMan(int x, int y) :Gobject(x, y)
	{
		this->speed = PLAYERSPEED;
		twCommand = tw = LEFT;
	}
	void action();
};



class Enermy :public Gobject//����
{
protected:
	void Catch();//�Ƿ�ץס����
	void virtual MakeDecision(bool b) = 0;//�˹�����ʵ��
	COLORREF color;
	virtual void AchiveCtrl();//���˳Զ�
public:
	static PacMan * player;
	void virtual Draw(HDC & hdc);
	Enermy(int x, int y) :Gobject(x, y)
	{
		this->speed = ENERMYSPEED;
		tw = LEFT;
		twCommand = UP;
	}
	void virtual action();
};



class RedOne :public Enermy//����ƶ�
{
protected:
	void virtual MakeDecision(bool b);
public:
	void Draw(HDC & hdc);
	RedOne(int x, int y) :Enermy(x, y)
	{
		color = RGB(255, 0, 0);
	}
};



class BlueOne :public RedOne//������
{
protected:
	void virtual MakeDecision(bool b);
public:
	void Draw(HDC & kdc);
	BlueOne(int x, int y) :RedOne(x, y)
	{
		color = RGB(0, 0, 255);
	}
};



class YellowOne :public RedOne//������
{
protected:
	void virtual MakeDecision(bool b);
public:
	void Draw(HDC & hdc);
	YellowOne(int x, int y) :RedOne(x, y)
	{
		color = RGB(200, 200, 10);
	}
};
