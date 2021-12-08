#include "AmmoManager.h"
#include "Player.h"
#include "KongAmmo.h"
#include "EntAmmo.h"


HRESULT AmmoManager::Init(Player* target)
{
	vecKongAmmos.resize(kongAmmoMaxCount);

	for (int i = 0; i < kongAmmoMaxCount; ++i)
	{
		vecKongAmmos[i] = new KongAmmo;
		vecKongAmmos[i]->Init();
	}

	vecEntAmmos.resize(entAmmoMaxCount);

	for (int i = 0; i < entAmmoMaxCount; ++i)
	{

		vecEntAmmos[i] = new EntAmmo;
		vecEntAmmos[i]->Init();
	}
	return S_OK;
}

void AmmoManager::Update()
{
	for (int i = 0; i < kongAmmoMaxCount; ++i)
	{
		vecKongAmmos[i]->Update();
	}

	for (int i = 0; i < entAmmoMaxCount; ++i)
	{
		vecEntAmmos[i]->Update();
	}
}

void AmmoManager::Render(HDC hdc)
{
	for (int i = 0; i < kongAmmoMaxCount; ++i)
	{
		vecKongAmmos[i]->Render(hdc);
	}

	for (int i = 0; i < entAmmoMaxCount; ++i)
	{
		vecEntAmmos[i]->Render(hdc);
	}
}

void AmmoManager::Release()
{
	for (int i = 0; i < kongAmmoMaxCount; ++i)
	{
		SAFE_RELEASE(vecKongAmmos[i]);
	}
	vecKongAmmos.clear();

	for (int i = 0; i < entAmmoMaxCount; ++i)
	{
		SAFE_RELEASE(vecEntAmmos[i]);
	}
	vecEntAmmos.clear();
}

void AmmoManager::EntFire(POINTFLOAT pos, int dir)
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

void AmmoManager::KongFire(POINTFLOAT pos, float angle, int dir)
{
	for (int i = 0; i < kongAmmoMaxCount; ++i)
	{
		// 리사이클 
		if (vecKongAmmos[i]->GetIsAlive())
		{
			continue;
		}

		vecKongAmmos[i]->IsFire(pos, angle, dir);
		break;
	}
}
