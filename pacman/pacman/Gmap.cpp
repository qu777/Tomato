#include "stdafx.h"
#include "Gmap.h"

int Gmap::LD = 36;
int Gmap::PD = 3;



//敌我双方出现位置没有豆子出现
void Gmap::Initop()
{
	peaMapData[E_ROW][E_ARRAY] = false;
	peaMapData[P_ROW][P_ARRAY] = false;
}



void Gmap::DrawMap(HDC& memDC)
{
	for (int i = 0; i<MAPLENTH; i++)
	{
		for (int j = 0; j<MAPLENTH; j++)
		{
			//绘制墙壁
			if (!mapData[i][j])
			{
				RECT rect;
				rect.left = j*LD;
				rect.top = i*LD;
				rect.right = (j + 1)*LD;
				rect.bottom = (i + 1)*LD;
				FillRect(memDC, &rect, CreateSolidBrush(color));

			}
		}
	}

}



void Gmap::DrawPeas(HDC& hdc)
{

	for (int i = 0; i<MAPLENTH; i++)
	{
		for (int j = 0; j<MAPLENTH; j++)
		{
			if (peaMapData[i][j])
			{
				Ellipse(hdc, (LD / 2 - PD) + j*LD, (LD / 2 - PD) + i*LD, (LD / 2 + PD) + j*LD, (LD / 2 + PD) + i*LD);

			}
		}
	}

}



Gmap::~Gmap()
{

}



//Stage_1成员定义:
#define A true
#define B false
bool Stage_1::initData[MAPLENTH][MAPLENTH] =
{
	B,B,B,B,B,B,B,B,A,B,B,B,B,B,B,B,B,//0
	B,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,B,//1
	B,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,B,//2
	B,A,A,A,A,B,B,B,B,B,B,B,A,A,A,A,B,//3
	B,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,B,//4
	B,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,B,//5
	B,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,B,//6
	B,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,B,//7
	A,A,A,A,A,A,A,B,A,B,A,A,A,A,A,A,A,//8
	B,A,A,A,A,A,A,B,B,B,A,A,A,A,A,A,B,//9
	B,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,B,//10
	B,A,A,A,A,B,A,A,A,A,A,A,A,B,A,A,B,//11
	B,A,A,A,B,B,B,A,A,A,A,A,B,B,B,A,B,//12
	B,A,A,A,A,B,A,A,A,A,A,A,A,B,A,A,B,//13
	B,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,B,//14
	B,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,B,//15
	B,B,B,B,B,B,B,B,A,B,B,B,B,B,B,B,B,//16	
};
#undef A
#undef B



Stage_1::Stage_1()
{
	color = RGB(140, 240, 240);
	for (int i = 0; i<MAPLENTH; i++)
	{
		for (int j = 0; j<MAPLENTH; j++)
		{
			this->mapData[i][j] = this->initData[i][j];
			this->peaMapData[i][j] = this->initData[i][j];
		}
	}
	//敌我双方出现位置没有豆子出现
	this->Initop();
}



//Stage_2成员定义
#define A true
#define B false
bool Stage_2::initData[MAPLENTH][MAPLENTH] =
{
	B,B,A,B,B,A,B,B,A,B,B,A,B,B,A,B,B,//0
	B,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,//1
	B,A,A,A,A,A,B,A,A,A,B,A,A,A,A,A,B,//2
	B,A,A,A,A,B,A,A,A,A,A,B,A,A,A,A,B,//3
	B,A,A,A,B,A,A,A,A,A,A,A,B,A,A,A,B,//4
	B,A,A,B,A,A,A,A,A,A,A,A,A,B,A,A,B,//5
	B,A,B,A,A,A,A,A,A,A,A,A,A,A,B,A,B,//6
	B,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,B,//7
	A,A,A,A,A,A,A,B,A,B,A,A,A,A,A,A,A,//8
	B,A,A,A,A,A,A,B,B,B,A,A,A,A,A,A,B,//9
	B,A,B,A,A,A,A,A,A,A,A,A,A,A,B,A,B,//10
	B,A,A,B,A,A,A,A,A,A,A,A,A,B,A,A,B,//11
	B,A,A,A,B,A,A,A,A,A,A,A,B,A,A,A,B,//12
	B,A,A,A,A,B,A,A,A,A,A,B,A,A,A,A,B,//13
	B,A,A,A,A,A,B,A,A,A,B,A,A,A,A,A,B,//14
	B,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,B,//15
	B,B,A,B,B,A,B,B,A,B,B,A,B,B,A,B,B,//16
};
#undef A
#undef B



Stage_2::Stage_2()
{
	color = RGB(240, 140, 140);
	for (int i = 0; i<MAPLENTH; i++)
	{
		for (int j = 0; j<MAPLENTH; j++)
		{
			this->mapData[i][j] = this->initData[i][j];
			this->peaMapData[i][j] = this->initData[i][j];
		}
	}
	//敌我双方出现位置没有豆子出现
	this->Initop();
}



//Stage_3成员定义
#define A true
#define B false
bool Stage_3::initData[MAPLENTH][MAPLENTH] =
{
	B,B,B,B,B,B,B,B,A,B,B,B,B,B,B,B,B,//0
	B,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,B,//1
	B,A,A,A,B,B,B,B,B,B,B,B,B,A,A,A,B,//2
	B,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,B,//3
	B,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,B,//4
	B,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,B,//5
	B,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,B,//6
	B,A,A,A,B,A,A,A,A,A,A,A,A,A,A,A,B,//7
	A,A,A,A,B,B,B,B,A,B,B,B,B,A,A,A,A,//8
	B,A,A,A,A,A,A,B,B,B,A,A,B,A,A,A,B,//9
	B,A,A,A,A,A,A,A,A,A,A,A,B,A,A,A,B,//10
	B,A,A,A,A,A,A,A,A,A,A,A,B,A,A,A,B,//11
	B,A,A,A,A,A,A,A,A,A,A,A,B,A,A,A,B,//12
	B,A,A,A,A,A,A,A,A,A,A,A,B,A,A,A,B,//13
	B,A,A,A,B,B,B,B,B,B,B,B,B,A,A,A,B,//14
	B,A,A,A,A,A,A,A,A,A,A,A,A,A,A,A,B,//15
	B,B,B,B,B,B,B,B,A,B,B,B,B,B,B,B,B,//16	
};
#undef A
#undef B



Stage_3::Stage_3()
{
	color = RGB(100, 300, 100);
	for (int i = 0; i<MAPLENTH; i++)
	{
		for (int j = 0; j<MAPLENTH; j++)
		{
			this->mapData[i][j] = this->initData[i][j];
			this->peaMapData[i][j] = this->initData[i][j];
		}
	}
	//敌我双方出现位置没有豆子出现
	this->Initop();
}
