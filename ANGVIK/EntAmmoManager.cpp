#include "EntAmmoManager.h"
#include "Player.h"
#include "EntAmmo.h"

HRESULT EntAmmoManager::Init(Player* target)
{
	vecEntAmmos.resize(entAmmoMaxCount);

	for (int i = 0; i < entAmmoMaxCount; ++i)
	{
		vecEntAmmos[i] = new EntAmmo;
		vecEntAmmos[i]->Init();
	}

	return S_OK;
}

void EntAmmoManager::Update()
{
	for (int i = 0; i < entAmmoMaxCount; ++i)
	{
		vecEntAmmos[i]->Update();
	}
}

void EntAmmoManager::Render(HDC hdc)
{
	for (int i = 0; i < entAmmoMaxCount; ++i)
	{
		vecEntAmmos[i]->Render(hdc);
	}
}

void EntAmmoManager::Release()
{
	for (int i = 0; i < entAmmoMaxCount; ++i)
	{
		SAFE_RELEASE(vecEntAmmos[i]);
	}
	vecEntAmmos.clear();
}

void EntAmmoManager::Fire(POINTFLOAT pos, int dir)
{
	for (int i = 0; i < entAmmoMaxCount; ++i)
	{
		// 리사이클 
		if (vecEntAmmos[i]->GetIsAlive())
		{
			continue;
		}

		float angle = 0.0f;

		if (dir > 0)
		{
			angle = (RANDOM(0, 25)) / 100.0f;
		}
		else
		{
			angle = (RANDOM(295, 315)) / 100.0f;
		}


		if (2 == RANDOM(1, 2))
		{
			angle *= -1;
		}

		float moveSpeed = (int)RANDOM(50, 150);

		vecEntAmmos[i]->IsFire(pos, angle, dir, moveSpeed);
	}
}
