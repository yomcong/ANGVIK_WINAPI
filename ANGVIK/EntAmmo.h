#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class EntAmmo : public GameObject
{
public:
	virtual ~EntAmmo() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void PlayAnimation();
	void PosUpdate();
	void DoAction();

	void IsFire(POINTFLOAT pos, float angle, int dir, float moveSpeed);
	inline const bool GetIsAlive() { return this->b_IsAlive; }

private:
	Image* ammoRight = nullptr;
	Image* ammoLeft = nullptr;

	bool b_IsAlive = false;

	// ????
	int direction = 1;

	POINT ammoFrame = { 0,0 };

	const POINT ammoMaxFrame = { 6, 0 };

	// ????
	float moveAngle = 0.0f;

	SubjectTag subTag = SubjectTag::AMMO;

};


