#pragma once
#include "Config.h"
#include "GameEntity.h"

// �츮�� ������ ���� ����
class Image;
class MainGame : public GameEntity
{
private:
	// Ÿ�̸�
	HANDLE hTimer = nullptr;

	// �����
	Image* backBuffer = nullptr;

	// ���콺 ��ǥ
	char mxText[16] = {};
	char myText[16] = {};

public:
	virtual ~MainGame() {}

	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};
