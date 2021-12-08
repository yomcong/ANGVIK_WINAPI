#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Trap : public GameObject
{
public:
	virtual ~Trap() = default;

	virtual HRESULT Init(POINTFLOAT pos, int dir);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	inline void SetIsCollision(bool b_isCollision) { this->b_isCollision = b_isCollision; }
	inline bool GetIsAlive() { return this->b_isAlive; }

private:
	Image* trap = nullptr;
	Image* R_trap = nullptr;

	float respawnCount = 0.0f;

	const POINT trapMaxFrame = { 0, 5 };

	bool b_isAlive = false;
	bool b_isCollision = false;


};

