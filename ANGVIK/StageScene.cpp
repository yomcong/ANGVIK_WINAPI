#include "StageScene.h"
#include "ImageManager.h"
#include "Image.h"
#include "CommonFunction.h"
#include "Player.h"
#include "Kong.h"
#include "MonsterManager.h"

#define stage1Width 6709
#define stage1Height 1290

// 맵 이동 디버깅용
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

	// 테스트용 (스크롤 미구현)
	mapPos.x = 6709 / 2;
	mapPos.y = 1290 / 2;

	// 플레이어
	player = new Player;
	player->Init();

	// 몬스터 매니저
	monsterManager = new MonsterManager;
	monsterManager->Init(player);


	return S_OK;
}

void StageScene::Update()
{
	player->Update();
	monsterManager->Update();

	// 디버그용 맵이동
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


	// 픽셀 맵 디버깅 용
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD7))
	{
		debugPixelMap == false ? debugPixelMap = true : debugPixelMap = false;
	}

}

void StageScene::Render(HDC hdc)
{
	stageBackgruond2->Render(hdc, mapPos.x - (int)CameraManager::GetSingleton()->GetPos().x,
		mapPos.y - (int)CameraManager::GetSingleton()->GetPos().y);	// 배경
	stageBackgruond2->Render(hdc, mapPos.x - (int)CameraManager::GetSingleton()->GetPos().x,
		mapPos.y/2 - (int)CameraManager::GetSingleton()->GetPos().y);	// 배경 좀더 위까지.

	stageBackgruond->Render(hdc, mapPos.x - (int)CameraManager::GetSingleton()->GetPos().x,
		mapPos.y - (int)CameraManager::GetSingleton()->GetPos().y);	// 맵 

	player->Render(hdc);
	monsterManager->Render(hdc);

	//kong->Render(hdc);

	// 픽셀 맵 디버깅
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