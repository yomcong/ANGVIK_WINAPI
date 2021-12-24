//#include "stdafx.h"
#include "AmmoManager.h"
#include "Player.h"
#include "KongAmmo.h"
#include "EntAmmo.h"
#include "playerWeapon.h"
#include "ItemManager.h"

HRESULT AmmoManager::Init(ItemManager* _itemManager)
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

	vecPlayerWeapons.resize(playerWeaponMaxCount);
	for (int i = 0; i < playerWeaponMaxCount; ++i)
	{
		vecPlayerWeapons[i] = new playerWeapon;
	}

	// 유연하게 할 방법 생각
	vecPlayerWeapons[0]->Init(SubjectTag::WEAPON, ItemGrade::GOLD, WeaponType::LANCE, _itemManager);
	vecPlayerWeapons[1]->Init(SubjectTag::WEAPON, ItemGrade::GOLD, WeaponType::LANCE, _itemManager);
	vecPlayerWeapons[2]->Init(SubjectTag::WEAPON, ItemGrade::SILVER, WeaponType::LANCE, _itemManager);
	vecPlayerWeapons[3]->Init(SubjectTag::WEAPON, ItemGrade::SILVER, WeaponType::LANCE, _itemManager);
	vecPlayerWeapons[4]->Init(SubjectTag::WEAPON, ItemGrade::GOLD, WeaponType::BOOMERANG, _itemManager);
	vecPlayerWeapons[5]->Init(SubjectTag::WEAPON, ItemGrade::GOLD, WeaponType::BOOMERANG, _itemManager);
	vecPlayerWeapons[6]->Init(SubjectTag::WEAPON, ItemGrade::SILVER, WeaponType::BOOMERANG, _itemManager);
	vecPlayerWeapons[7]->Init(SubjectTag::WEAPON, ItemGrade::SILVER, WeaponType::BOOMERANG, _itemManager);
	/*vecPlayerWeapons[(int)WeaponType::LANCE]->Init(SubjectTag::WEAPON, ItemGrade::GOLD, WeaponType::LANCE, _itemManager);
	vecPlayerWeapons[(int)WeaponType::BOOMERANG]->Init(SubjectTag::WEAPON, ItemGrade::GOLD, WeaponType::BOOMERANG, _itemManager);*/

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

	for (int i = 0; i < playerWeaponMaxCount; ++i)
	{
		vecPlayerWeapons[i]->Update();
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

	for (int i = 0; i < playerWeaponMaxCount; ++i)
	{
		vecPlayerWeapons[i]->Render(hdc);
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

	for (int i = 0; i < playerWeaponMaxCount; ++i)
	{
		SAFE_RELEASE(vecPlayerWeapons[i]);
	}
	vecPlayerWeapons.clear();
}

void AmmoManager::EntFire(POINTFLOAT pos, int dir)
{
	// 20발만 쏘게해야함
	int ammoCount = 0;
	for (int i = 0; i < 100; ++i)
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

		float moveSpeed = (float)RANDOM(50, 150);

		vecEntAmmos[i]->IsFire(pos, angle, dir, moveSpeed);

		++ammoCount;
		if (ammoCount >= 20)
		{
			break;
		}
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

void AmmoManager::WeaponAttack(SubjectTag _subTag, ItemGrade _itemGrade, WeaponType _weaponType, POINTFLOAT _pos, int _dir)
{
	if (_weaponType == WeaponType::LANCE)
	{
		if (_itemGrade == ItemGrade::GOLD)
		{
			for (int i = 0; i < 2; ++i)
			{
				if (vecPlayerWeapons[i]->GetIsAlive())
				{
					continue;
				}
				vecPlayerWeapons[i]->WeaponFire(_pos, _dir);
				break;
			}
		}
		else
		{
			for (int i = 2; i < 4; ++i)
			{
				if (vecPlayerWeapons[i]->GetIsAlive())
				{
					continue;
				}
				vecPlayerWeapons[i]->WeaponFire(_pos, _dir);
				break;
			}
		}
	}
	else if (_weaponType == WeaponType::BOOMERANG)
	{
		if (_itemGrade == ItemGrade::GOLD)
		{
			for (int i = 4; i < 6; ++i)
			{
				if (vecPlayerWeapons[i]->GetIsAlive())
				{
					continue;
				}
				vecPlayerWeapons[i]->WeaponFire(_pos, _dir);
				break;
			}
		}
		else
		{
			for (int i = 6; i < 8; ++i)
			{
				if (vecPlayerWeapons[i]->GetIsAlive())
				{
					continue;
				}
				vecPlayerWeapons[i]->WeaponFire(_pos, _dir);
				break;
			}
		}
		

	}

}
