#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Player;
class KongAmmoManager;
class Subject;
class Kong : public GameObject
{
public:
	virtual ~Kong() = default;

	virtual HRESULT Init(Player* target, POINTFLOAT pos);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void ToBeHit();
	void DoAction();
	void CheckWindow();
	void CheckAttackRange();

	Subject* GetSubject() { return subject; }

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

	Subject* subject = nullptr;

	// �Ѿ�
	KongAmmoManager* ammoManager = nullptr;
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

	float testElpsedCount = 0.0f;
	
	bool windowIn = false;
};

