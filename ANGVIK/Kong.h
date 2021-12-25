#pragma once
//#include "stdafx.h"
#include "Config.h"
#include "GameObject.h"
#include "Subject.h"

class Image;
class AmmoManager;
class Kong : public GameObject, public Subject
{
public:
	virtual ~Kong() = default;

	virtual HRESULT Init(POINTFLOAT pos, AmmoManager* _ammoManager);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void ToBeHit();
	void PlayAnimation();
	void CheckWindow();
	void CheckAttackRange();

private:
	Image* attackMotion = nullptr;
	Image* basicMotion = nullptr;
	Image* R_attackMotion = nullptr;
	Image* R_basicMotion = nullptr;
	Image* deathEffect = nullptr;

	// 애니메이션 프레임
	POINT basicFrame = { 0,0 };
	POINT attackFrame = { 0,0 };
	POINT deathEffectFrame = { 7,0 };

	// 총알
	AmmoManager* ammoManager = nullptr;
	// 타겟좌표
	Player* target = nullptr;

	const POINT attackMotionMaxFrame = { 8, 0 };
	const POINT basicMaxFrame = { 6, 0 };
	const POINT deathEffectMaxFrame = { 5,0 };

	RECT rangeRect = {};

	SubjectTag subTag = SubjectTag::MONSTER;
	MonsterType myType = MonsterType::KONG;
	

	// 사정거리 디버깅
	bool DBRangeRect = false;

	float AttackDeleyCount = 0.0f;
	
	bool b_windowIn = false;
	bool b_rangeInTarget = false;
};

