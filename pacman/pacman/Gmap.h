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
	static int LD;//�ϰ���ߴ�
	static int PD;//���ӵİ뾶
	void Initop();//����˫������λ��û�ж��ӳ���
	bool mapData[MAPLENTH][MAPLENTH];//�ϰ����߼���ͼ����
	COLORREF color;
public:
	bool peaMapData[MAPLENTH][MAPLENTH];//�����߼���ͼ����
	void DrawMap(HDC & hdc);//���Ƶ�ͼ
	void DrawPeas(HDC &hdc);//���ƶ���
	virtual ~Gmap();
	Gmap() {}
	friend class Gobject;//����������ʹ��ֱ�ߵ������յ����Ϣ����ײ���
	friend class Pacman;//���������ʶ��ӵ�ͼ
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