#pragma once
#include "Config.h"
#include "GameEntity.h"

class Trap;
class CollisionManager;
class TrapManager : public GameEntity
{
public:
	virtual ~TrapManager() = default;

	virtual HRESULT Init(CollisionManager* collisionManager);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void TrapSpawn();
	bool CheckCollision(RECT rect);


private:
	int trapMaxCount = 2;

	vector<Trap*> vecTraps = {};
	CollisionManager* collisionManager = nullptr;

};

