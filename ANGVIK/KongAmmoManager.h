#pragma once
#include "Config.h"
#include "GameEntity.h"

class Player;
class KongAmmo;
class KongAmmoManager : public GameEntity
{
public:
	virtual ~KongAmmoManager() = default;

	virtual HRESULT Init(Player* target);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void Fire(POINTFLOAT pos, float angle, int dir);

private:
	int DBammoMaxCount = 20;

	vector<KongAmmo*> vecAmmos = {};


};

