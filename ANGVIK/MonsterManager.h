#pragma once
#include "Config.h"
#include "GameEntity.h"

class Player;
class Kong;
class Monkey;
class Ent;
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
	void EntSpawn();

private:
	int kongMaxCount = 3;
	int MonkeyMaxCount = 3;
	int EntMaxCount = 3;

	vector<Kong*> vecKongs = {};
	vector<Monkey*> vecMonkeys = {};
	vector<Ent*> vecEnts = {};

	Player* target = nullptr;


};

