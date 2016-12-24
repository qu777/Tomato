// pacman.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "pacman.h"
#include "Gobject.h"
#define WLENTH 700
#define WHIGHT 740
#define MAX_LOADSTRING 100
#define STAGE_COUNT 3



// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名s



//游戏物体
PacMan* p;
Gobject* e1;
Gobject* e2;
Gobject* e3;
Gobject* e4;



//释放动态内存函数模板
template<class T>
void Realese(T t)
{
	if (t != NULL)
		delete t;
}



// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int, HWND&);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void ResetGObjects();
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance); //告诉编译器，已经使用了该变量，不必检测警告！
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此放置代码。
	int s_n = 0;//进行到的关卡数
	p = new PacMan(P_ROW, P_ARRAY);
	e1 = new RedOne(E_ROW, E_ARRAY);
	e2 = new RedOne(E_ROW, E_ARRAY);
	e3 = new BlueOne(E_ROW, E_ARRAY);
	e4 = new YellowOne(E_ROW, E_ARRAY);
	Gmap* MapArray[STAGE_COUNT] = { new Stage_1(),new Stage_2(),new Stage_3() };

	Gobject::pStage = MapArray[s_n];//初始化为第一关地图
	Enermy::player = p;
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);//从资源载入字符串
	LoadString(hInstance, IDC_PACMAN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);//注册该窗口应用程序

	// 执行应用程序初始化:
	HWND hWnd;//窗口句柄
	if (!InitInstance(hInstance, nCmdShow, hWnd))
	{
		return FALSE;
	}
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PACMAN));//调入加速键表
	DWORD t = 0;
	// 主消息循环:
	while (p->GetTw() != OVER && s_n<3)
	{
		if (p->Win())
		{
			HDC hdc = GetDC(hWnd);
			s_n++;
			ResetGObjects();
			if (s_n <3)
			{
				MessageBoxA(hWnd, "恭喜您过关", "吃豆子提示", MB_OK);
				Gobject::pStage = MapArray[s_n];
				RECT screenRect;
				screenRect.top = 0;
				screenRect.left = 0;
				screenRect.right = WLENTH;
				screenRect.bottom = WHIGHT;
				::FillRect(hdc, &screenRect, CreateSolidBrush(RGB(255, 255, 255)));
				Gobject::pStage->DrawMap(hdc);
			}
			continue;
		}
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000)
		{
			p->SetTwCommand(DOWN);
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000)
		{
			p->SetTwCommand(LEFT);
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000)
		{
			p->SetTwCommand(RIGHT);
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000)
		{
			p->SetTwCommand(UP);
		}
		else
		{
			if (GetTickCount() - t>60)
			{
				HDC hdc = GetDC(hWnd);
				e1->action();
				e2->action();
				e3->action();
				e4->action();
				p->action();
				Gobject::pStage->DrawPeas(hdc);
				e1->DrawBlank(hdc);
				e2->DrawBlank(hdc);
				e3->DrawBlank(hdc);
				e4->DrawBlank(hdc);
				p->DrawBlank(hdc);
				e1->Draw(hdc);
				e2->Draw(hdc);
				e3->Draw(hdc);
				e4->Draw(hdc);
				p->Draw(hdc);
				DeleteDC(hdc);
				t = GetTickCount();
			}
		}
	}
	Realese(e1);
	Realese(e2);
	Realese(e3);
	Realese(e4);
	for (int i = 0; i<STAGE_COUNT; i++)
	{
		Realese(MapArray[i]);
	}
	if (p->GetTw() == OVER)
	{
		MessageBoxA(hWnd, "Game Over!", "***游戏***", MB_OK);
	}
	else
	{
		MessageBoxA(hWnd, "You are the winner!", "***游戏***", MB_OK);
	}
	Realese(p);
	return (int)msg.wParam;
}

//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PACMAN));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_PACMAN);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND& hWnd)
{


	hInst = hInstance; // 将实例句柄存储在全局变量中

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, WLENTH, WHIGHT, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}
	MoveWindow(hWnd,300,0,628,670,true);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		Gobject::pStage->DrawMap(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		::exit(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
void ResetGObjects()
{
	p->SetPosition(P_ROW, P_ARRAY);
	e1->SetPosition(E_ROW, E_ARRAY);
	e2->SetPosition(E_ROW, E_ARRAY);
	e3->SetPosition(E_ROW, E_ARRAY);
	e4->SetPosition(E_ROW, E_ARRAY);
}