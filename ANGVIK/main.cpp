// main.cpp

#include <Windows.h>
#include "CommonFunction.h"
#include "MainGame.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

// ��������
POINT		g_ptMouse;
HINSTANCE	g_hInstance;
HWND		g_hWnd;
LPSTR		g_lpszClass = (LPSTR)TEXT("ANGVIK");
MainGame	g_mainGame;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance,
	_In_ LPSTR _lpszCmdParam, _In_ int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#endif
	//_CrtSetBreakAlloc(541);
	//_CrtSetBreakAlloc(379);
	//_CrtSetBreakAlloc(481);
	//_CrtSetBreakAlloc(417);


	// �����츦 �����ϱ� ���� �⺻ ����
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // �ڵ�����ȯ
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = _hInstance;
	wndClass.lpfnWndProc = WndProc;				// �Լ�������(�ݹ��Լ�)
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = g_lpszClass;
	wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;	// bit����

	// ������ Ŭ���� ���
	RegisterClass(&wndClass);

	// ������ ����
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW,
		WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y,
		NULL, NULL, _hInstance, NULL);

	SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y,
		WIN_SIZE_X, WIN_SIZE_Y);

	// ���ΰ��� �ʱ�ȭ
	g_mainGame.Init();


	// ������ ���
	ShowWindow(g_hWnd, nCmdShow);


	// �޽��� ť�� �ִ� �޽��� ó��
	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	// ���ΰ��� ����
	g_mainGame.Release();

	return (int)(message.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			//isUpdate = !isUpdate;
			break;
		}
		break;
	case WM_TIMER:
		g_mainGame.Update();

		break;
	case WM_PAINT:		// ������ ȭ���� �ٽ� �׷����� ��� �߻��ϴ� �޽���
		hdc = BeginPaint(g_hWnd, &ps);

		RECT rect;
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, WIN_SIZE_X, WIN_SIZE_Y, NULL);	//â ũ��
		GetClientRect(g_hWnd, &rect);
		SetViewportExtEx(hdc, rect.right, rect.bottom, NULL);

		g_mainGame.Render(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:	// �ݱ� ��ư �޽���ó�� (���α׷� ����)
		PostQuitMessage(0);
		return 0;
	}

	return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}
