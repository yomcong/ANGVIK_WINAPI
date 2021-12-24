#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Subject;
class Monkey : public GameObject
{
public:
	virtual ~Monkey() = default;

	virtual HRESULT Init(POINTFLOAT pos);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void ToBeHit();
	void PlayAnimation();
	void PosUpdate();
	void CheckWindow();
	void DoAction();

	Subject* GetSubject() { return subject; }

private:
	Image* monkey = nullptr;
	Image* R_monkey = nullptr;
	Image* deathEffect = nullptr;

	Subject* subject = nullptr;

	POINT deathEffectFrame = { 7,0 };

	const POINT monkeyMaxFrame = { 8, 0 };
	const POINT deathEffectMaxFrame = { 6,0 };

	SubjectTag subTag = SubjectTag::MONSTER;
	MonsterType myType = MonsterType::MONKEY;

	bool b_windowIn = false;

};

