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

	// �ִϸ��̼� ������
	POINT basicFrame = { 0,0 };
	POINT attackFrame = { 0,0 };
	POINT deathEffectFrame = { 7,0 };

	// �Ѿ�
	AmmoManager* ammoManager = nullptr;
	// Ÿ����ǥ
	Player* target = nullptr;

	const POINT attackMotionMaxFrame = { 8, 0 };
	const POINT basicMaxFrame = { 6, 0 };
	const POINT deathEffectMaxFrame = { 5,0 };

	RECT rangeRect = {};

	SubjectTag subTag = SubjectTag::MONSTER;
	MonsterType myType = MonsterType::KONG;
	

	// �����Ÿ� �����
	bool DBRangeRect = false;

	float AttackDeleyCount = 0.0f;
	
	bool b_windowIn = false;
	bool b_rangeInTarget = false;
};

