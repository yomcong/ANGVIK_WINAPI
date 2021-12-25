#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "Observer.h"

#define kongMaxCount 9
#define monkeyMaxCount 6
#define entMaxCount 3


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

	void MonkeyTriggerSpawn();

	bool CheckCollision(SubjectTag _subTage, RECT _shape, bool& _toStepOn);

	virtual void OnNotify(Subject* _subject, MonsterType _monsterType, SubjectTag _subjectTag, EventTag _eventTag) override;

private:
	//int kongMaxCount = 9;
	//int MonkeyMaxCount = 6;
	//int EntMaxCount = 3;

	bool kongInWindow[kongMaxCount] = { true };
	bool monkeyInWindow[monkeyMaxCount] = { true };
	bool entInWindow[entMaxCount] = { true };

	int currKongSpawn = 0;
	int currMonkeySpawn = 0;
	int currEntSpawn = 0;

	float spawnKongPosX[kongMaxCount] = { 880.0f, 1475.0f, 1910.0f, 2500.0f, 2970.0f, 3715.0f, 4340.0f, 5430.0f , 6315.0f };
	float spawnKongPosY[kongMaxCount] = { 385.0, 265.0f, 388.0f, 508.0f, 550.0f, 210.0f, 840.0f, 300.0f, 280.0f };

	float spawnMonkeyPosX[monkeyMaxCount] = { 500.0f, 850.0f, 1100.0f, 1400.0f, 2200.0f, 2300.0f };
	float spawnMonkeyPosY[monkeyMaxCount] = { 350.0f, 382.0f, 390.0f, 390.0f, 300.0f, 300.0f };

	float spawnEntPosX[entMaxCount] = { 1200.0f, 2970.0f,  4060.0f };
	float spawnEntPosY[entMaxCount] = { 450.0f, 747.0f,  886.0f };

	vector<Kong*> vecKongs = {};
	vector<Monkey*> vecMonkeys = {};
	vector<Ent*> vecEnts = {};

	AmmoManager* ammoManager = nullptr;
};

