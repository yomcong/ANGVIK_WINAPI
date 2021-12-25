#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "Observer.h"

class AmmoManager;
class Kong;
class Monkey;
class Ent;
class MonsterManager : public GameEntity, public Observer
{
public:
	virtual ~MonsterManager() = default;

	virtual HRESULT Init(AmmoManager* _ammoManager);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void KongSpawn();
	void MonkeySpawn();
	void EntSpawn();

	bool CheckCollision(SubjectTag _subTage, RECT _shape, bool &_toStepOn);

	virtual void OnNotify(Subject* _subject, MonsterType _monsterType, SubjectTag _subjectTag, EventTag _eventTag);

private:
	int kongMaxCount = 9;
	int MonkeyMaxCount = 6;
	int EntMaxCount = 3;
	
	bool kongWindow[9] = { true };
	bool monkeyWindow[6] = { true };
	bool entWindow[3] = { true };

	vector<Kong*> vecKongs = {};
	vector<Monkey*> vecMonkeys = {};
	vector<Ent*> vecEnts = {};

	AmmoManager* ammoManager = nullptr;

};

