//#include "stdafx.h"
#include "MainGame.h"
#include "Image.h"
#include "GameManager.h"

HRESULT MainGame::Init()
{
	ImageManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();
	MapColliderManager::GetSingleton()->Init();
	CameraManager::GetSingleton()->Init();
	ParticleManager::GetSingleton()->Init();
	Input::Init(g_hWnd);
	Timer::Init();

	SceneManager::GetSingleton()->ChangeScene("TitleScene");

	//srand((unsigned int)time(nullptr));

	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);
	
	backBuffer = new Image;

	backBuffer->Init("Image/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	return S_OK;
}

void MainGame::Update()
{
	Input::Update();

	SceneManager::GetSingleton()->Update();

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
	//TimerManager::GetSingleton()->Render(hBackBufferDC);

	//wsprintf(mxText, "Mouse x : %d", g_ptMouse.x);
	//TextOut(hBackBufferDC, WIN_SIZE_X - 150, 50, mxText, strlen(mxText));
	//wsprintf(myText, "Mouse y : %d", g_ptMouse.y);
	//TextOut(hBackBufferDC, WIN_SIZE_X - 150, 70, myText, strlen(myText));
#endif

	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	ImageManager::GetSingleton()->Release();

	SceneManager::GetSingleton()->Release();

	KillTimer(g_hWnd, 0);
}