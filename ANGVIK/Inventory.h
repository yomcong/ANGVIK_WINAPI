#pragma once
#include "Config.h"
#include "GameObject.h"

enum class InventoryType { MAIN, ITEMBOX, OILSBOX, SELECTITEM};
enum class SelectItem { EQUIPMENT, OILS };

class Image;
class Player;
class Inventory : public GameObject
{
public:
	virtual ~Inventory() = default;

	virtual HRESULT Init(Player* player);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void PosUpdate();
	void InventoryOpen(POINTFLOAT pos);
	bool GetItem(ItemType itemType, ItemGrade itemGrade, WeaponType weaponType = WeaponType::IDLE);

private:
	Image* inventoryUi = nullptr;
	Image* ItemBox = nullptr;
	Image* olis = nullptr;
	Image* seletItem = nullptr;

	Image* itemsText = nullptr;
	Image* oilsText = nullptr;
	Image* closeText = nullptr;
	Image* backText = nullptr;
	Image* equipText = nullptr;
	Image* dropText = nullptr;

	Image* selectBox = nullptr;

	vector<Image*> vecItems = {};
	vector<Image*> vecOils = {};
	vector<ItemInfo> vecItemInfos = {};
	vector<ItemInfo> vecOilsInfos = {};

	POINT itemTextPos = { 0, 0 };
	POINT oilsTextPos = { 0, 0 };
	POINT closeTextPos = { 0, 0 };
	POINT equipTextPos = { 0, 0 };
	POINT dropTextPos = { 0, 0 };
	POINT backTextPos = { 0, 0 };
	POINT selectBoxPos = { 0, 0 };
	POINT itemPos = { 0,0 };
	POINT oilsPos = { 0,0 };

	int seletedBoxFrame = 0;
	int selectedNum = 0;
	int selectedItemNum = 0;
	int itemMaximum = 4;
	int oilsMaximum = 3;
	InventoryType inventoryType = InventoryType::MAIN;

	Player* player = nullptr;

	SelectItem selectItemType = SelectItem::EQUIPMENT;

	
};

