#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "Observer.h"

#define TrapMaxCount 15
#define PlatformMaxCount 10

class Trap;
class Platform;
class TrapManager : public GameEntity, public Observer
{
public:
	virtual ~TrapManager() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void TrapSpawn();
	void PlatformSpawn();

	bool CheckCollision(RECT rect, bool &b_temp);

	virtual void OnNotify(Subject* _subject, MonsterType _monsterType, SubjectTag _subjectTag, EventTag _eventTag) override;

private:
	vector<Trap*> vecTraps = {};
	vector<Platform*> vecPlatforms = {};

	bool trapInWindow[TrapMaxCount] = { true };
	bool platformInWindow[PlatformMaxCount] = { true };
};

