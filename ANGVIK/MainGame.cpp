#include "MainGame.h"
#include "Image.h"
#include "GameManager.h"

HRESULT MainGame::Init()
{
	//KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();
	//GameManager::GetSingleton()->Init();
	MapColliderManager::GetSingleton()->Init();
	CameraManager::GetSingleton()->Init();
	ParticleManager::GetSingleton()->Init();

	Input::Init(g_hWnd);

	SceneManager::GetSingleton()->ChangeScene("TitleScene");

	srand((unsigned int)time(nullptr));

	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);
	
	backBuffer = new Image;

	backBuffer->Init("Image/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	return S_OK;
}

void MainGame::Update()
{
	TimerManager::GetSingleton()->Update();

	Input::Update();

	SceneManager::GetSingleton()->Update();

	MapColliderManager::GetSingleton()->Update();

	CameraManager::GetSingleton()->Update();

	ParticleManager::GetSingleton()->Update();

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	PatBlt(hBackBufferDC, 0, 0, WIN_SIZE_X, WIN_SIZE_Y, WHITENESS);

	SceneManager::GetSingleton()->Render(hBackBufferDC);
	
	ParticleManager::GetSingleton()->Render(hBackBufferDC);
	//fps Ç¥½Ã.
#ifdef _DEBUG
	TimerManager::GetSingleton()->Render(hBackBufferDC);

	wsprintf(mxText, "Mouse x : %d", g_ptMouse.x);
	TextOut(hBackBufferDC, WIN_SIZE_X - 150, 50, mxText, strlen(mxText));
	wsprintf(myText, "Mouse y : %d", g_ptMouse.y);
	TextOut(hBackBufferDC, WIN_SIZE_X - 150, 70, myText, strlen(myText));
#endif

	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	TimerManager::GetSingleton()->Release();

	ImageManager::GetSingleton()->Release();

	//KeyManager::GetSingleton()->Release();

	SceneManager::GetSingleton()->Release();

	KillTimer(g_hWnd, 0);
}


//LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
//{
//	switch (iMessage)
//	{
//	case WM_KEYDOWN:
//		switch (wParam)
//		{
//		case VK_SPACE:
//			break;
//		case VK_UP:
//			break;
//		case VK_DOWN:
//			break;
//		case VK_LEFT:
//			break;
//		case VK_RIGHT:
//			break;
//		}
//		break;
//
//	case WM_LBUTTONDOWN:
//		break;
//	case WM_LBUTTONUP:
//		break;
//	case WM_RBUTTONDOWN:
//		break;
//	case WM_MOUSEMOVE:
//		break;
//	}
//	return DefWindowProc(hWnd, iMessage, wParam, lParam);
//}
