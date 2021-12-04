#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Player;
class KongAmmoManager;
class Kong : public GameObject
{
public:
	virtual ~Kong() = default;

	virtual HRESULT Init(Player* target, POINTFLOAT pos);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();


private:
	Image* attackMotion = nullptr;
	Image* basicMotion = nullptr;

	POINT basicFrame = { 0,0 };
	POINT atackFrame = { 0,0 };

	KongAmmoManager* ammoManager = nullptr;
	Player* target = nullptr;

	POINTFLOAT renderPos = { 0, 0 };
	float frameCount = 0.0f;

	RECT DBrect = {};
	RECT testRect = {};
	bool DBKongRect = false;
	bool DBRangeRect = false;

	float testElpsedCount = 0.0f;
	

};

