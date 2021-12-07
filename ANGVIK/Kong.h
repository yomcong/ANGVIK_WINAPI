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
	Image* R_attackMotion = nullptr;
	Image* R_basicMotion = nullptr;

	// 애니메이션 프레임
	POINT basicFrame = { 0,0 };
	POINT atackFrame = { 0,0 };

	// 총알
	KongAmmoManager* ammoManager = nullptr;
	// 타겟좌표
	Player* target = nullptr;

	const POINT attackMotionMaxFrame = { 8, 0 };
	const POINT basicMaxFrame = { 6, 0 };

	// 충돌체크 함수로 제외할때 지역변수화 하기.
	RECT testRect = {};


	direction dir = direction::LEFT;
	// 사정거리 디버깅
	bool DBRangeRect = false;

	float testElpsedCount = 0.0f;
	

};

