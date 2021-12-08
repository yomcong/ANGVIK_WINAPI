#pragma once
#include "Config.h"
#include "GameEntity.h"


class EntAmmo;
class Player;
class KongAmmo;
class AmmoManager : public GameEntity
{
public:
	virtual ~AmmoManager() = default;

	virtual HRESULT Init(Player * target);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void EntFire(POINTFLOAT pos, int dir);
	void KongFire(POINTFLOAT pos, float angle, int dir);


private:
	int kongAmmoMaxCount = 7;
	int entAmmoMaxCount = 20;

	vector<KongAmmo*> vecKongAmmos = {};
	vector<EntAmmo*> vecEntAmmos = {};

};

