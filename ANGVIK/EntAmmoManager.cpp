#include "EntAmmoManager.h"
#include "EntAmmo.h"

HRESULT EntAmmoManager::Init(Player* target)
{
	vecAmmos.resize(DBammoMaxCount);

	for (int i = 0; i < DBammoMaxCount; ++i)
	{
		
		vecAmmos[i] = new EntAmmo;
		vecAmmos[i]->Init();
	}
	return S_OK;

}

void EntAmmoManager::Update()
{
	for (int i = 0; i < DBammoMaxCount; ++i)
	{
		vecAmmos[i]->Update();
	}

}

void EntAmmoManager::Render(HDC hdc)
{
	for (int i = 0; i < DBammoMaxCount; ++i)
	{
		vecAmmos[i]->Render(hdc);
	}

}

void EntAmmoManager::Release()
{
	for (int i = 0; i < DBammoMaxCount; ++i)
	{
		SAFE_RELEASE(vecAmmos[i]);
	}
	vecAmmos.clear();

}

void EntAmmoManager::Fire(POINTFLOAT pos, int dir)
{
	// 1.5~

	for (int i = 0; i < DBammoMaxCount; ++i)
	{
		// 리사이클 
		if (vecAmmos[i]->GetIsAlive())
		{
			continue;
		}
		
		float angle = 0.0f;

		if (dir > 0)
		{
			angle =( RANDOM(0, 25)) / 100.0f;
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
		
		vecAmmos[i]->IsFire(pos, angle, dir, moveSpeed);
	}
}
