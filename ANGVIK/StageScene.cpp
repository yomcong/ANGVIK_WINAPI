#include "StageScene.h"
#include "ImageManager.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Player.h"
#include "Kong.h"
#include "MonsterManager.h"
#include "TrapManager.h"
#include "CollisionManager.h"
#include "ItemManager.h"

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
	stageHiddenMap = ImageManager::GetSingleton()->FindImage("image/Stage/Stage1-Hidden.bmp");
	if (stageHiddenMap == nullptr)
	{
		return E_FAIL;
	}
	DBlogo = ImageManager::GetSingleton()->FindImage("image/etc/·Î°í.bmp");	// ¾Óºò ·Î°í
	if (DBlogo == nullptr)
	{
		return E_FAIL;
	}
	
	mapPos.x = 6709 / 2;
	mapPos.y = 1290 / 2;

	player = new Player;
	monsterManager = new MonsterManager;
	trapManager = new TrapManager;
	itemManager = new ItemManager;

	CollisionManager::GetSingleton()->AddPlayer(player);
	CollisionManager::GetSingleton()->AddMonsterManager(monsterManager);
	CollisionManager::GetSingleton()->AddTrapManager(trapManager);
	CollisionManager::GetSingleton()->AddItem(itemManager);

	player->Init();
	monsterManager->Init(player);
	trapManager->Init();
	itemManager->Init();

	return S_OK;
}

void StageScene::Update()
{
	if (DBstop == false)
	{
		player->Update();
		monsterManager->Update();
		trapManager->Update();
		itemManager->Update();
	}

	// È÷µç¸Ê µð¹ö±ë ÀÌÈÄ ¿ÉÀú¹ö·Î ¾Ë¸²º¸³»ÁÖ±â
	if (CameraManager::GetSingleton()->GetPos().x > 5060)
	{
		if (CameraManager::GetSingleton()->GetPos().y > 590 &&
			CameraManager::GetSingleton()->GetPos().y < 610)
		{
			b_hiddenMapDiscovery = true;
		}
	}


	// ÇÈ¼¿ ¸Ê µð¹ö±ë ¿ë
	if (Input::GetButtonDown(VK_NUMPAD7))
	{
		debugPixelMap == false ? debugPixelMap = true : debugPixelMap = false;
	}

	if (Input::GetButtonDown(VK_NUMPAD0))
	{
		DBstop = !DBstop;
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

	if (b_hiddenMapDiscovery == false)
	{
		stageHiddenMap->Render(hdc, mapPos.x - (int)CameraManager::GetSingleton()->GetPos().x, mapPos.y -(int)CameraManager::GetSingleton()->GetPos().y);
	}

	DBlogo->Render(hdc, 1000 - (int)CameraManager::GetSingleton()->GetPos().x, 200 - (int)CameraManager::GetSingleton()->GetPos().y);
	DBlogo->Render(hdc, 2000 - (int)CameraManager::GetSingleton()->GetPos().x, 200 - (int)CameraManager::GetSingleton()->GetPos().y);
	DBlogo->Render(hdc, 3000 - (int)CameraManager::GetSingleton()->GetPos().x, 200 - (int)CameraManager::GetSingleton()->GetPos().y);
	DBlogo->Render(hdc, 4000 - (int)CameraManager::GetSingleton()->GetPos().x, 200 - (int)CameraManager::GetSingleton()->GetPos().y);
	DBlogo->Render(hdc, 5000 - (int)CameraManager::GetSingleton()->GetPos().x, 200 - (int)CameraManager::GetSingleton()->GetPos().y);

	itemManager->Render(hdc);
	monsterManager->Render(hdc);
	trapManager->Render(hdc);
	player->Render(hdc);


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
	SAFE_RELEASE(itemManager);
}