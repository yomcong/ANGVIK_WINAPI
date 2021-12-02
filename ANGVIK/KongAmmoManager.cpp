#include "KongAmmoManager.h"
#include "Player.h"
#include "KongAmmo.h"

HRESULT KongAmmoManager::Init(Player* target)
{
	vecAmmos.resize(DBammoMaxCount);

	for (int i = 0; i < DBammoMaxCount; ++i)
	{
		vecAmmos[i] = new KongAmmo;
		vecAmmos[i]->Init();
	}
	return S_OK;
}

void KongAmmoManager::Update()
{
	for (int i = 0; i < DBammoMaxCount; ++i)
	{
		vecAmmos[i]->Update();
	}
}

void KongAmmoManager::Render(HDC hdc)
{
	for (int i = 0; i < DBammoMaxCount; ++i)
	{
		vecAmmos[i]->Render(hdc);
	}

}

void KongAmmoManager::Release()
{
	for (int i = 0; i < DBammoMaxCount; ++i)
	{
		SAFE_RELEASE(vecAmmos[i]);
	}
	vecAmmos.clear();
}

void KongAmmoManager::Fire(POINTFLOAT pos, float angle, int dir)
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
