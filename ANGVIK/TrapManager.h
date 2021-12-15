#pragma once
#include "Config.h"
#include "GameEntity.h"

class Trap;
class Platform;
class TrapManager : public GameEntity
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


private:
	int trapMaxCount = 2;
	int PlatformMaxCount = 2;

	vector<Trap*> vecTraps = {};
	vector<Platform*> vecPlatforms = {};
};

