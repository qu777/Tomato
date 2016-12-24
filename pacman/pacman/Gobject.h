#pragma once
#include"stdafx.h"
#include"Gmap.h"
#include<iostream>
#include<ctime>

const int PLAYERSPEED = 6;//玩家速度
const int ENERMYSPEED = 4;//敌人速度
const int LEGCOUNTS = 5;//敌人腿的数量
const int DISTANCE = 10;//图形范围
const int BLUE_ALERT = 8;//蓝色警戒范围
const int D_OFFSET = 2;//绘图误差
const int RD = (DISTANCE + D_OFFSET);

enum TWARDS { UP, DOWN, LEFT, RIGHT, OVER };//方向枚举

class Gobject//物体类
{
protected:
	int mX;
	int mY;
	TWARDS twCommand;//指令缓存
	POINT point;//中心坐标
	int dRow;//逻辑横坐标
	int dArray;//逻辑纵坐标
	int speed;//速度
	TWARDS tw;//朝向
	int frame;//帧数
	bool Achive();//判断物体是否到达逻辑坐标
	bool Collision();//逻辑碰撞检测，将物体摆放在合理的位置
	int PtTransform(int k);//将实际坐标转换为逻辑坐标
	virtual void AchiveCtrl();//到达逻辑点后跟新数据
public:
	void SetPosition(int Row, int Array);
	void DrawBlank(HDC & hdc);
	void virtual Draw(HDC & kdc) = 0;//绘制对象
	static Gmap * pStage;//指向地图类的指针，设置为静态，使所有子类对象都能使用相同的地图
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
	void virtual action() = 0;//数据变更的表现
	int GetRow();
	int GetArray();
};



class PacMan :public Gobject//玩家控制的对象
{
protected:
	virtual void AchiveCtrl();//重写虚函数
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



class Enermy :public Gobject//敌人
{
protected:
	void Catch();//是否抓住大嘴
	void virtual MakeDecision(bool b) = 0;//人工智能实现
	COLORREF color;
	virtual void AchiveCtrl();//敌人吃豆
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



class RedOne :public Enermy//随机移动
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



class BlueOne :public RedOne//守卫者
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



class YellowOne :public RedOne//扰乱者
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
