#pragma once
#include "Config.h"
#include "GameEntity.h"

class Player;
class MonsterManager;
class TrapManager;
class CollisionManager : public GameEntity
{
public:
	virtual ~CollisionManager() = default;

	virtual HRESULT Init(Player* player, MonsterManager* monsterManager, TrapManager* trapManager);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void AddObject(SubjectTag subject, EventTag object, RECT* shape);
	void CheckCollision(SubjectTag subject, EventTag object, RECT shape);
	SubjectTag testCheck(SubjectTag subjectTag, RECT shape);
						
private:
	vector<RECT*> vecRects = {};

	Player* player = nullptr;
	MonsterManager* monsterManager = nullptr;
	TrapManager*   trapManager = nullptr;

};

