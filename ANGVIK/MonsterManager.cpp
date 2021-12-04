#include "MonsterManager.h"
#include "Player.h"
#include "Kong.h"

// 몬스터 스폰위치는 정해져있는 구역 안에서 랜덤.
//  

HRESULT MonsterManager::Init(Player* target)
{
	kongMaxCount = 3;

	this->target = target;

	KongSpawn();


	return S_OK;
}

void MonsterManager::Update()
{
	for (int i = 0; i < vecKong.size(); ++i)
	{
		vecKong[i]->Update();
	}
}

void MonsterManager::Render(HDC hdc)
{
	for (int i = 0; i < vecKong.size(); ++i)
	{
		vecKong[i]->Render(hdc);
	}
}

void MonsterManager::Release()
{
	for (int i = 0; i < vecKong.size(); ++i)
	{
		SAFE_RELEASE(vecKong[i]);
	}
	vecKong.clear();
}

void MonsterManager::KongSpawn()
{
	kongMaxCount = RANDOM(1, kongMaxCount);
	vecKong.resize(kongMaxCount);
	float spawnPosX[] = { 350.0f, 500.0f, 850.0f };
	float spawnPosY[] = { 360.0f, 275.0f, 382.0f };

	for (int i = 0; i < vecKong.size(); ++i)
	{
		vecKong[i] = new Kong;
		vecKong[i]->Init(target, { spawnPosX[i],spawnPosY[i] });
	}

}

