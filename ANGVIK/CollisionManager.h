#pragma once
#include "Config.h"
#include "Singleton.h"

class Player;
class MonsterManager;
class TrapManager;
class ItemManager;
class CollisionManager : public Singleton<CollisionManager>
{
public:
	virtual ~CollisionManager() = default;

	virtual HRESULT Init();

	void AddPlayer(Player* player);
	void AddMonsterManager(MonsterManager* monsterManager);
	void AddTrapManager(TrapManager* trapManager);
	void AddItem(ItemManager* itemManager);
	void AddObject(SubjectTag subject, EventTag object, RECT* shape);
	bool CheckCollision(SubjectTag _subject, RECT _shape, EventTag _eventTag = EventTag::IDLE);
	POINTFLOAT RangeCheckCollision(SubjectTag _subject, RECT _shape, EventTag _eventTag);
	void CheckItem(RECT shape);
						
private:
	vector<RECT*> vecRects = {};

	Player* player = nullptr;
	MonsterManager* monsterManager = nullptr;
	TrapManager*   trapManager = nullptr;
	ItemManager* itemManager = nullptr;
};

