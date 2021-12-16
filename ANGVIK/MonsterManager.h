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

	bool CheckCollision(RECT shape, bool &toStepOn);

	virtual void OnNotify(Subject* subject, MonsterType monsterType, SubjectTag subjectTag, EventTag eventTag);

private:
	int kongMaxCount = 4;
	int MonkeyMaxCount = 6;
	int EntMaxCount = 3;
	
	bool kongWindow[4] = { true };
	bool monkeyWindow[6] = { true };
	bool entWindow[3] = { true };

	vector<Kong*> vecKongs = {};
	vector<Monkey*> vecMonkeys = {};
	vector<Ent*> vecEnts = {};

	Player* target = nullptr;


};

