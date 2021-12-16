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

	Titem[0] = new TestItem;
	Titem[1] = new TestItem;

	Titem[0]->Init({ 340, 350 }, ItemType::ARMOR, ItemGrade::GOLD);
	Titem[1]->Init({ 350, 350 }, ItemType::SHOES, ItemGrade::GOLD);

	vecItems.push_back(Titem[0]);
	vecItems.push_back(Titem[1]);

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

void ItemManager::CreateItem(MonsterType monsterType)
{
	switch (monsterType)
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
	//Item* tempItem = itemFactory[type]->CreateTank();
	//tempItem->Init(type, tile, tank, tankManager, this);

	//vecItems.push_back(tempItem);
}

bool ItemManager::CheckCollision(RECT shape, ItemType &itemType, ItemGrade &itemGrade)
{
	RECT tempRect = {};

	for (int i = 0; i < vecItems.size(); ++i)
	{
		if (IntersectRect(&tempRect, &shape, vecItems[i]->GetShapeAddress()))
		{
			itemType = vecItems[i]->GetItemType();
			itemGrade = vecItems[i]->GetItemGrade();
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


