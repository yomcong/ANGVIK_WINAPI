#include "StageScene.h"
#include "ImageManager.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Player.h"
#include "Kong.h"
#include "MonsterManager.h"
#include "TrapManager.h"
#include "CollisionManager.h"

#define stage1Width 6709
#define stage1Height 1290

// ¸Ê ÀÌµ¿ µð¹ö±ë¿ë


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

	player = new Player;
	monsterManager = new MonsterManager;
	trapManager = new TrapManager;
	collisionManager = new CollisionManager;

	player->Init(collisionManager);
	monsterManager->Init(player, collisionManager);
	trapManager->Init(collisionManager);
	collisionManager->Init(player, monsterManager, trapManager);
	
	return S_OK;
}

void StageScene::Update()
{
	player->Update();
	monsterManager->Update();
	trapManager->Update();
	// ÇÈ¼¿ ¸Ê µð¹ö±ë ¿ë
	if (Input::GetButtonDown(VK_NUMPAD7))
	{
		debugPixelMap == false ? debugPixelMap = true : debugPixelMap = false;
	}

}

void StageScene::Render(HDC hdc)
{
	stageBackgruond2->Render(hdc, mapPos.x - (int)CameraManager::GetSingleton()->GetPos().x,
		mapPos.y - (int)CameraManager::GetSingleton()->GetPos().y);	// ¹è°æ

	// ¹è°æ ÀÓ½Ã·Î ·£´õ
	stageBackgruond2->Render(hdc, mapPos.x - (int)CameraManager::GetSingleton()->GetPos().x - 5,
		mapPos.y/2 - (int)CameraManager::GetSingleton()->GetPos().y);

	stageBackgruond->Render(hdc, mapPos.x - (int)CameraManager::GetSingleton()->GetPos().x,
		mapPos.y - (int)CameraManager::GetSingleton()->GetPos().y);	// ¸Ê 

	player->Render(hdc);
	monsterManager->Render(hdc);
	trapManager->Render(hdc);

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
	SAFE_RELEASE(trapManager);

}