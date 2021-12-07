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

void EntAmmoManager::Fire(POINTFLOAT pos, float angle, int dir)
{
	for (int i = 0; i < DBammoMaxCount; ++i)
	{
		// 리사이클 
		if (vecAmmos[i]->GetIsAlive())
		{
			continue;
		}

		vecAmmos[i]->IsFire(pos, angle, dir);
		break;
	}
}
