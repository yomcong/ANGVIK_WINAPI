#include "TrapManager.h"
#include "Trap.h"
#include "Platform.h"

HRESULT TrapManager::Init()
{
	TrapSpawn();
	PlatformSpawn();

	return S_OK;
}

void TrapManager::Update()
{
	for (int i = 0; i < trapMaxCount; ++i)
	{
		vecTraps[i]->Update();
	}
	for (int i = 0; i < PlatformMaxCount; ++i)
	{
		vecPlatforms[i]->Update();
	}
}

void TrapManager::Render(HDC hdc)
{
	for (int i = 0; i < trapMaxCount; ++i)
	{
		vecTraps[i]->Render(hdc);
	}
	for (int i = 0; i < PlatformMaxCount; ++i)
	{
		vecPlatforms[i]->Render(hdc);
	}
}

void TrapManager::Release()
{
	for (int i = 0; i < trapMaxCount; ++i)
	{
		SAFE_RELEASE(vecTraps[i]);
	}
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

	float spawnPosX[] = { 990.0f, 700.0f };
	float spawnPosY[] = { 445.0f, 250.0f };

	for (int i = 0; i < trapMaxCount; ++i)
	{
		vecTraps[i] = new Trap;
		vecTraps[i]->Init({ spawnPosX[i],spawnPosY[i] });
	}
}

void TrapManager::PlatformSpawn()
{
	vecPlatforms.resize(PlatformMaxCount);

	float spawnPosX[] = { 2628.0f, 2860.0f, 2861.0f, 2736.0f, 2740.0f, 2740.0f };
	float spawnPosY[] = { 441.0f, 485.0f, 602.0f, 417.0f, 530.0f, 643.0f };

	for (int i = 0; i < PlatformMaxCount; ++i)
	{
		int dir = i < PlatformMaxCount / 2;
		vecPlatforms[i] = new Platform;
		vecPlatforms[i]->Init({ spawnPosX[i],spawnPosY[i] }, dir);
	}
}

bool TrapManager::CheckCollision(RECT rect, bool& b_temp)
{
	for (int i = 0; i < trapMaxCount; ++i)
	{
		// 렉트충돌비교가 아니라 따로 해야함
		RECT temprect = {};
		if (IntersectRect(&temprect, vecTraps[i]->GetShapeAddress(), &rect))
		{
			return true;
		}
	}

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