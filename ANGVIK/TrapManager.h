#pragma once
#include "Config.h"
#include "GameEntity.h"

class Trap;
class TrapManager : public GameEntity
{
public:
	virtual ~TrapManager() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void TrapSpawn();
	bool CheckCollision(RECT rect);


private:
	int trapMaxCount = 2;

	vector<Trap*> vecTraps = {};

};

