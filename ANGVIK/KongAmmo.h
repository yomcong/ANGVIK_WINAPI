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
	Image* ammoEffect = nullptr;
	Image* R_ammoEffect = nullptr;

	bool b_IsAlive = false;
	bool b_ISHit = false;

	POINT ammoFrame = { 0,0 };
	POINT effectFrame = { 0, 0 };

	const POINT ammoMaxFrame = { 5, 0 };
	const POINT effectMaxFrame = { 6, 0 };

	// °¢µµ
	float moveAngle = 0.0f;
};

