#pragma once
#include "Config.h"
#include "GameEntity.h"

class EntAmmo;
class Player;
class KongAmmo;
class playerWeapon;
class ItemManager;
class AmmoManager : public GameEntity
{
public:
	virtual ~AmmoManager() = default;

	virtual HRESULT Init(ItemManager* _itemManager);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void EntFire(POINTFLOAT pos, int dir);
	void KongFire(POINTFLOAT pos, float angle, int dir);
	void WeaponAttack(SubjectTag _subTag,ItemGrade _itemGrade, WeaponType _weaponType, POINTFLOAT _pos, int _dir);

private:
	int kongAmmoMaxCount = 20;
	int entAmmoMaxCount = 100;
	int playerWeaponMaxCount = 10;

	vector<KongAmmo*> vecKongAmmos = {};
	vector<EntAmmo*> vecEntAmmos = {};
	vector<playerWeapon*> vecPlayerWeapons = {};
};

