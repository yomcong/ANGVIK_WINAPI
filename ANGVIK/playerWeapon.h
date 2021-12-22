#pragma once
#include "stdafx.h"
#include "Config.h"
#include "GameObject.h"

class Image;
class ItemManager;
class playerWeapon : public GameObject
{
public:
	virtual ~playerWeapon() = default;

	virtual HRESULT Init(SubjectTag _subTag, ItemGrade _itemGrade, WeaponType _weaponType, ItemManager* _itemManager);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void PlayAnimation();
	void PosUpdate();
	bool WeaponFire(POINTFLOAT _pos, int _dir);

private:
	Image* weaponImage = nullptr;
	Image* R_weaponImage = nullptr;

	int weaponFrame = {};
	const int weaponMaxFrame = 0;

	SubjectTag subTag = SubjectTag::WEAPON;
	ItemGrade  myGrade = ItemGrade::IDLE;
	WeaponType myType = WeaponType::IDLE;

	ItemManager* itemManager = nullptr;

};

