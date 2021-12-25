#pragma once
#include "Config.h"
#include "GameEntity.h"
 

class Image;
class Item;
class ItemFactory;
class TestItem;
class ItemManager : public GameEntity
{
public:
	virtual ~ItemManager() = default;

	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void CreateItem(SubjectTag _subTag, POINTFLOAT _pos, WeaponType _weaponType = WeaponType::IDLE, ItemGrade _itemGrade = ItemGrade::IDLE, MonsterType _monsterType = MonsterType::IDLE);
	bool CheckCollision(RECT shape, ItemType& itemType, ItemGrade& itemGrade, WeaponType& weaponType);
	//void UseItem();


private:
	/*vector<Item*> vecItems = {};
	Item* item = nullptr;

	ItemFactory* itemFactory[6] = {};*/

	TestItem* Titem[6] = {};
	vector<TestItem*> vecItems = {};

};

