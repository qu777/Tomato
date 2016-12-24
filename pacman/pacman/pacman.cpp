// pacman.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "pacman.h"
#include "Gobject.h"
#define WLENTH 700
#define WHIGHT 740
#define MAX_LOADSTRING 100
#define STAGE_COUNT 3



// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������s



//��Ϸ����
PacMan* p;
Gobject* e1;
Gobject* e2;
Gobject* e3;
Gobject* e4;



//�ͷŶ�̬�ڴ溯��ģ��
template<class T>
void Realese(T t)
{
	if (t != NULL)
		delete t;
}



// �˴���ģ���а����ĺ�����ǰ������:
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

	UNREFERENCED_PARAMETER(hPrevInstance); //���߱��������Ѿ�ʹ���˸ñ��������ؼ�⾯�棡
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: �ڴ˷��ô��롣
	int s_n = 0;//���е��Ĺؿ���
	p = new PacMan(P_ROW, P_ARRAY);
	e1 = new RedOne(E_ROW, E_ARRAY);
	e2 = new RedOne(E_ROW, E_ARRAY);
	e3 = new BlueOne(E_ROW, E_ARRAY);
	e4 = new YellowOne(E_ROW, E_ARRAY);
	Gmap* MapArray[STAGE_COUNT] = { new Stage_1(),new Stage_2(),new Stage_3() };

	Gobject::pStage = MapArray[s_n];//��ʼ��Ϊ��һ�ص�ͼ
	Enermy::player = p;
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);//����Դ�����ַ���
	LoadString(hInstance, IDC_PACMAN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);//ע��ô���Ӧ�ó���

	// ִ��Ӧ�ó����ʼ��:
	HWND hWnd;//���ھ��
	if (!InitInstance(hInstance, nCmdShow, hWnd))
	{
		return FALSE;
	}
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PACMAN));//������ټ���
	DWORD t = 0;
	// ����Ϣѭ��:
	while (p->GetTw() != OVER && s_n<3)
	{
		if (p->Win())
		{
			HDC hdc = GetDC(hWnd);
			s_n++;
			ResetGObjects();
			if (s_n <3)
			{
				MessageBoxA(hWnd, "��ϲ������", "�Զ�����ʾ", MB_OK);
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
		MessageBoxA(hWnd, "Game Over!", "***��Ϸ***", MB_OK);
	}
	else
	{
		MessageBoxA(hWnd, "You are the winner!", "***��Ϸ***", MB_OK);
	}
	Realese(p);
	return (int)msg.wParam;
}

//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, HWND& hWnd)
{


	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��:
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
		// TODO: �ڴ���������ͼ����...
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

// �����ڡ������Ϣ�������
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