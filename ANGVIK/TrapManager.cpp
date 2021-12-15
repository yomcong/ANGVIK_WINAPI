#include "TrapManager.h"
#include "Trap.h"
#include "Platform.h"

HRESULT TrapManager::Init()
{
	//TrapSpawn();
	PlatformSpawn();

	return S_OK;
}

void TrapManager::Update()
{
	/*for (int i = 0; i < trapMaxCount; ++i)
	{
		vecTraps[i]->Update();
	}*/
	for (int i = 0; i < PlatformMaxCount; ++i)
	{
		vecPlatforms[i]->Update();
	}
}

void TrapManager::Render(HDC hdc)
{
	/*for (int i = 0; i < trapMaxCount; ++i)
	{
		vecTraps[i]->Render(hdc);
	}*/
	for (int i = 0; i < PlatformMaxCount; ++i)
	{
		vecPlatforms[i]->Render(hdc);
	}
}

void TrapManager::Release()
{
	/*for (int i = 0; i < trapMaxCount; ++i)
	{
		SAFE_RELEASE(vecTraps[i]);
	}*/
	//vecTraps.clear();
	for (int i = 0; i < PlatformMaxCount; ++i)
	{
		SAFE_RELEASE(vecPlatforms[i]);
	}
	vecPlatforms.clear();
}

void TrapManager::TrapSpawn()
{
	vecTraps.resize(trapMaxCount);

	float spawnPosX[] = { 450.0f, 90.0f };
	float spawnPosY[] = { 310.0f, 410.0f };

	for (int i = 0; i < trapMaxCount; ++i)
	{
		int dir = i < trapMaxCount / 2;
		vecTraps[i] = new Trap;
		vecTraps[i]->Init({ spawnPosX[i],spawnPosY[i] }, dir);
	}
}

void TrapManager::PlatformSpawn()
{
	vecPlatforms.resize(PlatformMaxCount);

	float spawnPosX[] = { 450.0f, 90.0f };
	float spawnPosY[] = { 310.0f, 410.0f };

	for (int i = 0; i < PlatformMaxCount; ++i)
	{
		int dir = i < PlatformMaxCount / 2;
		vecPlatforms[i] = new Platform;
		vecPlatforms[i]->Init({ spawnPosX[i],spawnPosY[i] }, dir);
	}
}

bool TrapManager::CheckCollision(RECT rect, bool& b_temp)
{
	//for (int i = 0; i < trapMaxCount; ++i)
	//{
	//	// 충돌 최적화 해보기
	//	if (false == vecTraps[i]->GetIsAlive())
	//	{
	//		continue;
	//	}

	//	// 렉트충돌비교가 아니라 따로 해야함
	//	RECT testRect = {};
	//	if (IntersectRect(&testRect, vecTraps[i]->GetShapeAddress(), &rect))
	//	{
	//		vecTraps[i]->SetIsCollision(true);
	//		b_temp = true;
	//		isCollision = true;
	//		continue;
	//	}
	//	vecTraps[i]->SetIsCollision(false);
	//}

	for (int i = 0; i < PlatformMaxCount; ++i)
	{
		// 충돌 최적화 해보기
		if (false == vecPlatforms[i]->GetIsAlive())
		{
			continue;
		}

		// 렉트충돌비교가 아니라 따로 해야함
		RECT tempRect = {};
		if (IntersectRect(&tempRect, vecPlatforms[i]->GetShapeAddress(), &rect))
		{
			if (tempRect.left >= vecPlatforms[i]->GetShapeAddress()->left &&
				tempRect.right <= vecPlatforms[i]->GetShapeAddress()->right &&
				(((vecPlatforms[i]->GetShapeAddress()->top + vecPlatforms[i]->GetShapeAddress()->bottom) / 2) + vecPlatforms[i]->GetShapeAddress()->top) / 2 > tempRect.bottom)
			{
				vecPlatforms[i]->SetIsCollision(true);
				b_temp = true;
				return true;
			}
		}
	}
	return false;
}