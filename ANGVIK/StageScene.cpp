#include "StageScene.h"
#include "ImageManager.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Player.h"
#include "Kong.h"
#include "MonsterManager.h"

#define stage1Width 6709
#define stage1Height 1290

// ¸Ê ÀÌµ¿ µð¹ö±ë¿ë
#define moveSpeed 5.0f


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

	// Å×½ºÆ®¿ë (½ºÅ©·Ñ ¹Ì±¸Çö)
	mapPos.x = 6709 / 2;
	mapPos.y = 1290 / 2;

	// ÇÃ·¹ÀÌ¾î
	player = new Player;
	player->Init();

	// ¸ó½ºÅÍ ¸Å´ÏÀú
	monsterManager = new MonsterManager;
	monsterManager->Init(player);


	return S_OK;
}

void StageScene::Update()
{
	player->Update();
	monsterManager->Update();

	// µð¹ö±×¿ë ¸ÊÀÌµ¿
	//if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD6))
	//{
	//	mapPos.x = 6709 / 2 - CameraManager::GetSingleton()->GetPos().x;	//(int)moveSpeed;
	//}
	//if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD4))
	//{
	//	if (mapPos.x > 6709 / 2)
	//	{
	//		mapPos.x = 6709 / 2;
	//	}
	//	else
	//	{
	//		mapPos.x = 6709 / 2 - CameraManager::GetSingleton()->GetPos().x;	//(int)moveSpeed;
	//	}
	//}
	//if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD2))
	//{
	//	mapPos.y = 1290 / 2 - CameraManager::GetSingleton()->GetPos().y; //(int)moveSpeed;
	//}
	//if (KeyManager::GetSingleton()->IsStayKeyDown(VK_NUMPAD8))
	//{
	//	if (mapPos.y > 1290 / 2)
	//	{
	//		mapPos.y = 1290 / 2;
	//	}
	//	else
	//	{
	//		mapPos.y = 1290 / 2 - CameraManager::GetSingleton()->GetPos().y; //(int)moveSpeed
	//	}
	//}


	// ÇÈ¼¿ ¸Ê µð¹ö±ë ¿ë
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD7))
	{
		debugPixelMap == false ? debugPixelMap = true : debugPixelMap = false;
	}

}

void StageScene::Render(HDC hdc)
{
	stageBackgruond2->Render(hdc, mapPos.x - (int)CameraManager::GetSingleton()->GetPos().x,
		mapPos.y - (int)CameraManager::GetSingleton()->GetPos().y);	// ¹è°æ
	stageBackgruond->Render(hdc, mapPos.x - (int)CameraManager::GetSingleton()->GetPos().x,
		mapPos.y - (int)CameraManager::GetSingleton()->GetPos().y);	// ¸Ê 

	player->Render(hdc);
	monsterManager->Render(hdc);

	//kong->Render(hdc);

	// ÇÈ¼¿ ¸Ê µð¹ö±ë
	if (debugPixelMap)
	{
		stagePixelMap->Render(hdc, mapPos.x - (int)CameraManager::GetSingleton()->GetPos().x, 
			mapPos.y - (int)CameraManager::GetSingleton()->GetPos().y);
	}
}

void StageScene::Release()
{
	SAFE_RELEASE(player);
	SAFE_RELEASE(monsterManager);


}