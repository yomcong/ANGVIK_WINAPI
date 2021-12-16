#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class TestItem : public GameObject
{
public:
	virtual ~TestItem() = default;

	virtual HRESULT Init(POINTFLOAT pos, ItemType itemType, ItemGrade itemGrade);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	inline const ItemType GetItemType() { return this->itemType; }
	inline const ItemGrade GetItemGrade() { return this->itemGrade; }
	

private:
	Image* itemImage = nullptr;

	SubjectTag subTag = SubjectTag::ITEM;
	ItemType itemType = ItemType::IDLE;
	ItemGrade itemGrade = ItemGrade::IDLE;

};

