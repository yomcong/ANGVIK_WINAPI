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

	void PlayAnimation();
	void PosUpdate();
	void DoAction();

	void IsFire(POINTFLOAT pos, float angle, int dir);
	inline const bool GetIsAlive() { return this->b_IsAlive; }

private:
	Image* ammoRight = nullptr;
	Image* ammoLeft = nullptr;

	bool b_IsAlive = false;

	POINT ammoFrame = { 0,0 };

	const POINT ammoMaxFrame = { 5, 0 };

	// °¢µµ
	float moveAngle = 0.0f;

	SubjectTag subTag = SubjectTag::AMMO;
};

