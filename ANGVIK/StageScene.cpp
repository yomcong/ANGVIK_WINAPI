//#include "stdafx.h"
#include "StageScene.h"
#include "ImageManager.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Player.h"
#include "MonsterManager.h"
#include "TrapManager.h"
#include "ItemManager.h"
#include "AmmoManager.h"

#define stage1Width 6709
#define stage1Height 1290

#define backgroundSize 1024

HRESULT StageScene::Init()
{
	mainStage = ImageManager::GetSingleton()->FindImage("image/Stage/Stage1-Background.bmp");
	if (mainStage == nullptr)
	{
		return E_FAIL;
	}
	stageBackgruond_2 = ImageManager::GetSingleton()->FindImage("image/Stage/Stage1-Background2.bmp");
	if (stageBackgruond_2 == nullptr)
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
	stageBackgruond_1 = ImageManager::GetSingleton()->FindImage("image/Stage/Stage1-bg1.bmp");
	if (stageBackgruond_1 == nullptr)
	{
		return E_FAIL;
	}
	mapPos.x = stage1Width / 2;
	mapPos.y = stage1Height / 2;

	backgroundMapPos.x = backgroundSize / 2;
	backgroundMapPos.y = backgroundSize / 2;

	player = new Player;
	monsterManager = new MonsterManager;
	trapManager = new TrapManager;
	itemManager = new ItemManager;
	ammoManager = new AmmoManager;

	CollisionManager::GetSingleton()->AddPlayer(player);
	CollisionManager::GetSingleton()->AddMonsterManager(monsterManager);
	CollisionManager::GetSingleton()->AddTrapManager(trapManager);
	CollisionManager::GetSingleton()->AddItem(itemManager);

	player->Init(ammoManager);
	player->GetSubject()->AddObserver(this);
	monsterManager->Init(ammoManager);
	trapManager->Init();
	itemManager->Init();
	ammoManager->Init(itemManager);

	return S_OK;
}

void StageScene::Update()
{
	// µð¹ö±ë¿ë ÀÏ½ÃÁ¤Áö
	if (DBstop==false)
	{
		player->Update();
		monsterManager->Update();
		trapManager->Update();
		itemManager->Update();
		ammoManager->Update();
	}

	if (Input::GetButtonDown(VK_NUMPAD0))
	{
		DBstop = !DBstop;
	}
	// ÇÈ¼¿ ¸Ê µð¹ö±ë ¿ë
	if (Input::GetButtonDown(VK_NUMPAD7))
	{
		DBPixelMap = !DBPixelMap;
	}
}

void StageScene::Render(HDC hdc)
{
	// ¹è°æ
	stageBackgruond_2->Render(hdc, mapPos.x - (int)CameraManager::GetSingleton()->GetPos().x,
		(int)mapPos.y - (int)CameraManager::GetSingleton()->GetPos().y);

	stageBackgruond_1->Render(hdc, (int)backgroundMapPos.x, (int)backgroundMapPos.y);

	//¸Ê
	mainStage->Render(hdc, mapPos.x - (int)CameraManager::GetSingleton()->GetPos().x,
		mapPos.y - (int)CameraManager::GetSingleton()->GetPos().y);

	// ¼û°ÜÁø Áö¿ª 
	if (b_hiddenMapDiscovery == false)
	{
		stageHiddenMap->Render(hdc, mapPos.x - (int)CameraManager::GetSingleton()->GetPos().x, mapPos.y - (int)CameraManager::GetSingleton()->GetPos().y);
	}

	itemManager->Render(hdc);
	monsterManager->Render(hdc);
	trapManager->Render(hdc);
	ammoManager->Render(hdc);
	player->Render(hdc);

	// ÇÈ¼¿ ¸Ê µð¹ö±ë
	if (DBPixelMap)
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
	SAFE_RELEASE(ammoManager);
}	

void StageScene::OnNotify(Subject* _subject, MonsterType _monsterType, SubjectTag _subjectTag, EventTag _eventTag)
{
	switch (_subjectTag)
	{
	case SubjectTag::PLAYER:
		switch (_eventTag)
		{
		case EventTag::ITEMDROP:
		{
			ItemInfo tempItemInfo = {};

			tempItemInfo = player->GetItemInfo();
			itemManager->CreateItem(player->GetPos(), tempItemInfo.itemType, tempItemInfo.weaponType, tempItemInfo.itemgrade);
			break;
		}
		case EventTag::FINDHIDDENMAP:
			b_hiddenMapDiscovery = true;
			break;
		case EventTag::MONSTERTRIGGER:
			if (oneTriggerOn == false)
			{
				monsterManager->MonkeyTriggerSpawn();
				oneTriggerOn = true;
			}
			else
			{
				monsterManager->MonkeyTriggerSpawn2();
			}
			break;
		}
		break;
	}
}
