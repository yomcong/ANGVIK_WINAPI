//#include "stdafx.h"
#include "ItemManager.h"
#include "Image.h"
#include "Item.h"
#include "ItemFactory.h"
#include "TestItem.h"

HRESULT ItemManager::Init()
{
	/*itemFactory[0] = new HelmetItemFactory;
	itemFactory[1] = new ClockItemFactory;
	itemFactory[2] = new ShovelItemFactory;
	itemFactory[3] = new StarItemFactory;
	itemFactory[4] = new GrenadeItemFactory;
	itemFactory[5] = new TankLifeItemFactory;*/

	// µð¹ö±ëÁß 
	for (int i = 0; i < ItemInitCount; ++i)
	{
		Titem[i] = new TestItem;
	}

	Titem[0]->Init({ 800, 350 }, ItemType::ARMOR, ItemGrade::SILVER);
	Titem[1]->Init({ 830, 350 }, ItemType::SHOES, ItemGrade::SILVER);
	Titem[2]->Init({ 860, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::LANCE);
	Titem[3]->Init({ 890, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::SWORD);
	Titem[4]->Init({ 920, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::BOOMERANG);
	Titem[5]->Init({ 950, 350 }, ItemType::OLIS, ItemGrade::GOLD, WeaponType::IDLE);

	for (int i = 0; i < ItemInitCount; ++i)
	{
		vecItems.push_back(Titem[i]);
	}

	return S_OK;
}

void ItemManager::Update()
{
	for (int i = 0; i < vecItems.size(); ++i)
	{
		vecItems[i]->Update();
	}

}

void ItemManager::Render(HDC hdc)
{
	for (int i = 0; i < vecItems.size(); ++i)
	{
		vecItems[i]->Render(hdc);
	}
}

void ItemManager::Release()
{
	/*for (int i=0; i<6; i++)
	{
		SAFE_DELETE(itemFactory[i]);
	}*/

	for (int i = 0; i < vecItems.size(); ++i)
	{
		SAFE_RELEASE(vecItems[i]);
	}
	vecItems.clear();

}

void ItemManager::CreateItem(POINTFLOAT _pos, ItemType _itemType, WeaponType _weaponType, ItemGrade _itemGrade, MonsterType _monsterType)
{
	vecItems.emplace_back();
	vecItems[vecItems.size() - 1] = new TestItem;
	vecItems[vecItems.size() - 1]->Init(_pos, _itemType, _itemGrade, _weaponType);
}

bool ItemManager::CheckCollision(RECT shape, ItemType& itemType, ItemGrade& itemGrade, WeaponType& weaponType)
{
	RECT tempRect = {};

	for (int i = 0; i < vecItems.size(); ++i)
	{
		if (IntersectRect(&tempRect, &shape, vecItems[i]->GetShapeAddress()))
		{
			itemType = vecItems[i]->GetItemType();
			itemGrade = vecItems[i]->GetItemGrade();
			weaponType = vecItems[i]->GetWeaponType();
			SAFE_DELETE(vecItems[i]);
			vecItems.erase(vecItems.begin() + i);
			return true;
		}
	}
	return false;
}

//void ItemManager::UseItem()
//{
//	for (int i = 0; i < vecItems.size(); ++i)
//	{
//		if (vecItems[i]->GetUseItem())
//		{
//			SAFE_DELETE(vecItems[i]);
//			vecItems.erase(vecItems.begin() + i);
//		}
//	}
//}


