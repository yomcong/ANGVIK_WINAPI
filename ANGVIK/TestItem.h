#pragma once
#include "stdafx.h"
#include "Config.h"
#include "GameObject.h"

class Image;
class TestItem : public GameObject
{
public:
	virtual ~TestItem() = default;

	virtual HRESULT Init(POINTFLOAT pos, ItemType itemType, ItemGrade itemGrade, WeaponType weaponType = WeaponType::IDLE);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	inline const ItemType GetItemType() { return this->itemType; }
	inline const ItemGrade GetItemGrade() { return this->itemGrade; }
	inline const WeaponType GetWeaponType() { return this->weaponType; }


private:
	Image* itemImage = nullptr;

	SubjectTag subTag = SubjectTag::ITEM;
	ItemType itemType = ItemType::IDLE;
	WeaponType weaponType = WeaponType::IDLE;
	ItemGrade itemGrade = ItemGrade::IDLE;

};

