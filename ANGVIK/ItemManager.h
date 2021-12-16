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

	void CreateItem(MonsterType monsterType);
	bool CheckCollision(RECT shape, ItemType &itemType, ItemGrade &itemGrade);
	//void UseItem();


private:
	/*vector<Item*> vecItems = {};
	Item* item = nullptr;

	ItemFactory* itemFactory[6] = {};*/

	TestItem* Titem[2] = {};
	vector<TestItem*> vecItems = {};

};

