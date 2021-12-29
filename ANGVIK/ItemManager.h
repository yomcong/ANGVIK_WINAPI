#pragma once
#include "Config.h"
#include "GameEntity.h"
 
#define ItemInitCount 11

class Image;
class Item;
class ItemFactory;
class Item;
class ItemManager : public GameEntity
{
public:
	virtual ~ItemManager() = default;

	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void CreateItem(POINTFLOAT _pos, ItemType _itemType, WeaponType _weaponType = WeaponType::IDLE, ItemGrade _itemGrade = ItemGrade::IDLE, MonsterType _monsterType = MonsterType::IDLE);
	bool CheckCollision(RECT shape, ItemType& itemType, ItemGrade& itemGrade, WeaponType& weaponType);

private:
	Item* Titem[ItemInitCount] = {};
	vector<Item*> vecItems = {};
};

