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


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE _hPrevInstance,
	_In_ LPSTR _lpszCmdParam, _In_ int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#endif
	// 윈도우를 생성하기 위한 기본 셋팅
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 핸들형변환
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = _hInstance;
	wndClass.lpfnWndProc = WndProc;				// 함수포인터(콜백함수)
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = g_lpszClass;
	wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;	// bit연산

	// 윈도우 클래스 등록
	RegisterClass(&wndClass);

	// 윈도우 생성
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW,
		WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y,
		NULL, NULL, _hInstance, NULL);

	SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y,
		WIN_SIZE_X, WIN_SIZE_Y);

	// 메인게임 초기화
	g_mainGame.Init();


	// 윈도우 출력
	ShowWindow(g_hWnd, nCmdShow);

	MSG message = {};
	HDC hdc;
	PAINTSTRUCT ps;
	while (true)
	{
		if (PeekMessage(&message, nullptr, NULL, NULL, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{

				break;
			}

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			if (Timer::CanUpdate())
			{
				g_mainGame.Update();

				hdc = BeginPaint(g_hWnd, &ps);

				RECT rect;
				SetMapMode(hdc, MM_ANISOTROPIC);
				SetWindowExtEx(hdc, WIN_SIZE_X, WIN_SIZE_Y, NULL);	//창 크기
				GetClientRect(g_hWnd, &rect);
				SetViewportExtEx(hdc, rect.right, rect.bottom, NULL);

				g_mainGame.Render(hdc);

				EndPaint(g_hWnd, &ps);
			}
		}
	}
	// 메인게임 해제
	g_mainGame.Release();

	return (int)(message.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_DESTROY:	// 닫기 버튼 메시지처리 (프로그램 종료)
		PostQuitMessage(0);
		return 0;

	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);// g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}
