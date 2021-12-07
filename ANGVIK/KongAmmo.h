#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class KongAmmo : public GameObject
{
public:
	virtual ~KongAmmo() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void IsFire(POINTFLOAT pos, float angle, int dir);
	inline const bool GetIsAlive() { return this->b_IsAlive; }

private:
	Image* ammoRight = nullptr;
	Image* ammoLeft = nullptr;

	bool b_IsAlive = false;

	// 방향
	int direction = 1;

	POINT ammoFrame = { 0,0 };


	const POINT ammoMaxFrame = { 6, 0 };

	// 각도
	float moveAngle = 0.0f;
};

