//#include "stdafx.h"
#include "ItemManager.h"
#include "Image.h"
#include "Item.h"
#include "Item.h"

HRESULT ItemManager::Init()
{
	for (int i = 0; i < ItemInitCount; ++i)
	{
		Titem[i] = new Item;
	}

	Titem[0]->Init({ 800, 350 }, ItemType::ARMOR, ItemGrade::SILVER);
	Titem[1]->Init({ 830, 350 }, ItemType::SHOES, ItemGrade::SILVER);
	Titem[2]->Init({ 860, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::LANCE);
	Titem[3]->Init({ 890, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::SWORD);
	Titem[4]->Init({ 920, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::BOOMERANG);
	Titem[5]->Init({ 950, 350 }, ItemType::OLIS, ItemGrade::GOLD, WeaponType::IDLE);
	Titem[6]->Init({ 2500, 350 }, ItemType::ARMOR, ItemGrade::SILVER);
	Titem[7]->Init({ 2530, 350 }, ItemType::SHOES, ItemGrade::SILVER);
	Titem[8]->Init({ 2550, 350 }, ItemType::OLIS, ItemGrade::GOLD, WeaponType::IDLE);
	Titem[9]->Init({ 2570, 350 }, ItemType::OLIS, ItemGrade::GOLD, WeaponType::IDLE);
	Titem[10]->Init({ 2600, 350 }, ItemType::ARMOR, ItemGrade::SILVER);

	/*Titem[6]->Init({ 440, 350 }, ItemType::ARMOR, ItemGrade::SILVER);
	Titem[7]->Init({ 480, 350 }, ItemType::SHOES, ItemGrade::SILVER);
	Titem[15]->Init({ 520, 350 }, ItemType::ARMOR, ItemGrade::SILVER);
	Titem[16]->Init({ 560, 350 }, ItemType::SHOES, ItemGrade::SILVER);
	Titem[8]->Init({ 600, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::LANCE);
	Titem[9]->Init({ 640, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::SWORD);
	Titem[10]->Init({ 680, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::BOOMERANG);
	Titem[17]->Init({ 750, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::LANCE);
	Titem[18]->Init({ 790, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::SWORD);
	Titem[19]->Init({ 820, 350 }, ItemType::WEAPON, ItemGrade::SILVER, WeaponType::BOOMERANG);
	Titem[11]->Init({ 700, 350 }, ItemType::OLIS, ItemGrade::GOLD, WeaponType::IDLE);
	Titem[12]->Init({ 710, 350 }, ItemType::OLIS, ItemGrade::GOLD, WeaponType::IDLE);
	Titem[13]->Init({ 720, 350 }, ItemType::OLIS, ItemGrade::GOLD, WeaponType::IDLE);
	Titem[14]->Init({ 730, 350 }, ItemType::OLIS, ItemGrade::GOLD, WeaponType::IDLE);*/


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
	for (int i = 0; i < vecItems.size(); ++i)
	{
		SAFE_RELEASE(vecItems[i]);
	}
	vecItems.clear();
}

void ItemManager::CreateItem(POINTFLOAT _pos, ItemType _itemType, WeaponType _weaponType, ItemGrade _itemGrade, MonsterType _monsterType)
{
	vecItems.emplace_back();
	vecItems[vecItems.size() - 1] = new Item;
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


