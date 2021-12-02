#include "StageScene.h"
#include "ImageManager.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Player.h"
#include "Kong.h"


#define stage1Width 6709
#define stage1Height 1290


// �� �̵� ������
#define moveSpeed 5.0f

// ī�޶� ��ũ�� �����

// ��� �����
// (ex : int ���� float ���� ��ȯ)


HRESULT StageScene::Init()
{
	stageBackgruond = ImageManager::GetSingleton()->FindImage("image/Stage/Stage1-Background.bmp");
	if (stageBackgruond == nullptr)
	{
		return E_FAIL;
	}
	stageBackgruond2 = ImageManager::GetSingleton()->FindImage("image/Stage/Stage1-Background2.bmp");
	if (stageBackgruond2 == nullptr)
	{
		return E_FAIL;
	}
	stagePixelMap = ImageManager::GetSingleton()->FindImage("image/Stage/Stage1-test.bmp");
	if (stagePixelMap == nullptr)
	{
		return E_FAIL;
	}

	// �׽�Ʈ�� (��ũ�� �̱���)
	mapPos.x = 6709 / 2;
	mapPos.y = 1290 / 2;

	// �÷��̾�
	player = new Player;
	player->Init();

	// ���� ��
	kong = new Kong;
	kong->Init(player);

	return S_OK;
}

void StageScene::Update()
{
	player->Update();
	kong->Update();
	
	// ����׿� ���̵�
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD6))
	{
		mapPos.x -= (int)moveSpeed;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD4))
	{
		if(mapPos.x < 6709/2)
			mapPos.x += (int)moveSpeed;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD2))
	{
		mapPos.y -= (int)moveSpeed;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD8))
	{
		if (mapPos.y < 1290 / 2)
			mapPos.y += (int)moveSpeed;
	}

	// �ȼ� �� ����� ��
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD7))
	{
		debugPixelMap == false ? debugPixelMap = true : debugPixelMap = false;
	}

}

void StageScene::Render(HDC hdc)
{
	stageBackgruond2->Render(hdc, mapPos.x, mapPos.y);	// ���
	stageBackgruond->Render(hdc, mapPos.x, mapPos.y);	// �� 

	player->Render(hdc);
	kong->Render(hdc);

	if (debugPixelMap)
	{
		stagePixelMap->Render(hdc, mapPos.x, mapPos.y);	//�ȼ� ��
	}
}

void StageScene::Release()
{
	SAFE_RELEASE(player);
	SAFE_RELEASE(kong);

}