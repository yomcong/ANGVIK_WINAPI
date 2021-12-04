#pragma once
#include "Config.h"
#include "GameEntity.h"

class Player;
class Kong;
class MonsterManager : public GameEntity
{
public:
	virtual ~MonsterManager() = default;

	virtual HRESULT Init(Player* target);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void KongSpawn();

private:
	int kongMaxCount = 3;


	vector<Kong*> vecKong = {};
	Player* target = nullptr;

};

