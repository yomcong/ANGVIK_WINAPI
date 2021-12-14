#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Player;
class Subject;
class Monkey : public GameObject
{
public:
	virtual ~Monkey() = default;

	virtual HRESULT Init(Player * target, POINTFLOAT pos);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	Subject* GetSubject() { return subject; }

private:
	Image* monkey = nullptr;
	Image* R_monkey = nullptr;

	Player* target = nullptr;

	Subject* subject = nullptr;

	const POINT monkeyMaxFrame = { 8, 0 };

	SubjectTag subTag = SubjectTag::MONSTER;
	MonsterType myType = MonsterType::MONKEY;

	bool windowIn = false;

};

