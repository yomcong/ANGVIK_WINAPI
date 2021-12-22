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
	for (int i = 0; i < 11; ++i)
	{
		Titem[i] = new TestItem;
	}

	Titem[0]->Init({ 340, 350 }, ItemType::ARMOR, ItemGrade::GOLD);
	Titem[1]->Init({ 350, 350 }, ItemType::SHOES, ItemGrade::GOLD);
	Titem[2]->Init({ 400, 350 }, ItemType::WEAPON, ItemGrade::GOLD, WeaponType::LANCE);
	Titem[3]->Init({ 450, 350 }, ItemType::WEAPON, ItemGrade::GOLD, WeaponType::SWORD);
	Titem[4]->Init({ 500, 350 }, ItemType::WEAPON, ItemGrade::GOLD, WeaponType::BOOMERANG);
	Titem[5]->Init({ 520, 350 }, ItemType::OLIS, ItemGrade::GOLD, WeaponType::IDLE);
	Titem[6]->Init({ 540, 350 }, ItemType::OLIS, ItemGrade::GOLD, WeaponType::IDLE);
	Titem[7]->Init({ 560, 350 }, ItemType::OLIS, ItemGrade::GOLD, WeaponType::IDLE);
	Titem[8]->Init({ 580, 350 }, ItemType::ARMOR, ItemGrade::GOLD);
	Titem[9]->Init({ 250, 350 }, ItemType::WEAPON, ItemGrade::GOLD, WeaponType::LANCE);
	Titem[10]->Init({ 200, 350 }, ItemType::WEAPON, ItemGrade::GOLD, WeaponType::SWORD);

	for (int i = 0; i < 11; ++i)
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


