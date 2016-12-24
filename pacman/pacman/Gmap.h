#pragma once
#include"stdafx.h"
#include<list>
#include<Windows.h>

const int MAPLENTH = 17;
const int P_ROW = 9;
const int P_ARRAY = 6;
const int E_ROW = 8;
const int E_ARRAY = 8;
using std::list;
class Gmap
{
protected:
	static int LD;//障碍物尺寸
	static int PD;//豆子的半径
	void Initop();//敌我双方出现位置没有豆子出现
	bool mapData[MAPLENTH][MAPLENTH];//障碍物逻辑地图点阵
	COLORREF color;
public:
	bool peaMapData[MAPLENTH][MAPLENTH];//豆子逻辑地图点阵
	void DrawMap(HDC & hdc);//绘制地图
	void DrawPeas(HDC &hdc);//绘制豆子
	virtual ~Gmap();
	Gmap() {}
	friend class Gobject;//允许物体类使用直线的起点和终点的信息做碰撞检测
	friend class Pacman;//允许大嘴访问豆子地图
};
class Stage_1 :public Gmap
{
private:
	bool static initData[MAPLENTH][MAPLENTH];
public:
	Stage_1();
};
class Stage_2 :public Gmap
{
private:
	bool static initData[MAPLENTH][MAPLENTH];
public:
	Stage_2();
};
class Stage_3 :public Gmap
{
private:
	bool static initData[MAPLENTH][MAPLENTH];
public:
	Stage_3();
};