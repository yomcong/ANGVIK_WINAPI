#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "Observer.h"

class Player;
class Kong;
class Monkey;
class Ent;
class MonsterManager : public GameEntity, public Observer
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

	virtual void OnNotify(Subject* subject, SubjectTag subjectTag, EventTag eventTag);

private:
	int kongMaxCount = 3;
	int MonkeyMaxCount = 3;
	int EntMaxCount = 3;
	
	bool KongWindow[3] = { false };

	vector<Kong*> vecKongs = {};
	vector<Monkey*> vecMonkeys = {};
	vector<Ent*> vecEnts = {};

	Player* target = nullptr;


};

