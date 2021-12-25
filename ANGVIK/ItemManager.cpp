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
	for (int i = 0; i < 6; ++i)
	{
		Titem[i] = new TestItem;
	}

	Titem[0]->Init({ 800, 350 }, ItemType::ARMOR, ItemGrade::SILVER);
	Titem[1]->Init({ 830, 350 }, ItemType::SHOES, ItemGrade::SILVER);
	Titem[2]->Init({ 860, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::LANCE);
	Titem[3]->Init({ 890, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::SWORD);
	Titem[4]->Init({ 920, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::BOOMERANG);
	Titem[5]->Init({ 950, 350 }, ItemType::OLIS, ItemGrade::GOLD, WeaponType::IDLE);

	for (int i = 0; i < 6; ++i)
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

void ItemManager::CreateItem(SubjectTag _subTag, POINTFLOAT _pos, WeaponType _weaponType, ItemGrade _itemGrade, MonsterType _monsterType)
{
	switch (_subTag)
	{
	case SubjectTag::MONSTER:
		switch (_monsterType)
		{
		case MonsterType::KONG:
			break;
		case MonsterType::MONKEY:
			break;
		case MonsterType::ENT:
			break;
		default:
			break;
		}
		break;
	case SubjectTag::WEAPON:
		switch (_weaponType)
		{
		case WeaponType::BOOMERANG:
			vecItems.emplace_back();
			vecItems[vecItems.size() - 1] = new TestItem;
			vecItems[vecItems.size() - 1]->Init(_pos, ItemType::WEAPON, _itemGrade, _weaponType);
			break;
		case WeaponType::LANCE:
			vecItems.emplace_back();
			vecItems[vecItems.size() - 1] = new TestItem;
			vecItems[vecItems.size() - 1]->Init(_pos, ItemType::WEAPON, _itemGrade, _weaponType);
			break;
		default:
			break;
		}
		break;
	}



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


