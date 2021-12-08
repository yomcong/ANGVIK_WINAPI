#pragma once
#include "Config.h"
#include "GameEntity.h"

class Player;
class EntAmmo;
class EntAmmoManager : public GameEntity
{
public:
	virtual ~EntAmmoManager() = default;

	virtual HRESULT Init(Player * target);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void Fire(POINTFLOAT pos, int dir);

private:
	int DBammoMaxCount = 20;

	vector<EntAmmo*> vecAmmos = {};
};

