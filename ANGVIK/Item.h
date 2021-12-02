//#pragma once
//#include "Config.h"
//#include "GameObject.h"
// 
//
//class Image;
//class Tank;
//class TankManager;
//class ItemManager;
//class Item : public GameObject
//{
//private:
//	Image* itemImage = nullptr;
//	Image* itemScore = nullptr;
//	int itemType = 0;
//	int itemTile = 0;
//	int elapsedcount = 0;
//	bool useItem = false;
//
//	GameEntity* stageInfo = nullptr;
//	Tank* tank = nullptr;
//	TankManager* tankManager = nullptr;
//
//	ItemManager* itemManager = nullptr;
//	RECT rc = {};
//	
//public:
//	HRESULT Init(int type, int tile, Tank* tank, TankManager* tankManager, TILE_INFO* tileInfo, ItemManager* itemManager);
//	void Update();
//	void Render(HDC hdc);
//	void Release();
//	virtual void UseItem() = 0;
//
//	inline Tank* GetTank() { return tank; }
//	inline TankManager* GetEnemyManager() { return tankManager; };
//	inline int GetType() { return this->itemType; } // const ������ ���� ������..
//	inline ItemManager* GetItemManager() { return itemManager; }
//	inline void SetUseItem(bool useItem) { this->useItem = useItem; }
//	inline bool GetUseItem() { return this->useItem; }
//	inline RECT* GetAddressRect() { return &this->rc; }
//	inline RECT GetRect() { return this->rc; }
//
//	Item() {};
//	virtual ~Item() {} 
//};
//
//class HelmetItem : public Item
//{
//public:
//	virtual void UseItem() override;
//
//	HelmetItem() {};
//	virtual ~HelmetItem() {}
//};
//
//class ClockItem : public Item
//{
//public:
//	virtual void UseItem() override;
//
//	ClockItem() {};
//	virtual ~ClockItem() {}
//};
//
//class ShovelItem : public Item
//{
//public:
//	virtual void UseItem() override;
//
//	ShovelItem() {};
//	virtual ~ShovelItem() {}
//};
//
//class StarItem : public Item
//{
//public:
//	virtual void UseItem() override;
//
//	StarItem() {};
//	virtual ~StarItem() {}
//};
//
//class GrenadeItem : public Item
//{
//public:
//	virtual void UseItem() override;
//
//	GrenadeItem() {};
//	virtual ~GrenadeItem() {}
//};
//
//class TankLifeItem : public Item
//{
//public:
//	virtual void UseItem() override;
//
//	TankLifeItem() {};
//	virtual ~TankLifeItem() {}
//};