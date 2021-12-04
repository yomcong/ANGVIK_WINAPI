#pragma once
#include "Config.h"
#include "GameEntity.h"

class Player;
class Kong;
class Monkey;
class MonsterManager : public GameEntity
{
public:
	virtual ~MonsterManager() = default;

	virtual HRESULT Init(Player* target);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void KongSpawn();
	void MonkeySpawn();

private:
	int kongMaxCount = 3;
	int MonkeyMaxCount = 3;

	vector<Kong*> vecKongs = {};
	vector<Monkey*> vecMonkeys = {};
	Player* target = nullptr;


};

