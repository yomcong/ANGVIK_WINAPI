#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Player;
class Monkey : public GameObject
{
public:
	virtual ~Monkey() = default;

	virtual HRESULT Init(Player * target, POINTFLOAT pos);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

private:
	Image* monkey = nullptr;
	Image* R_monkey = nullptr;

	Player* target = nullptr;

	const POINT monkeyMaxFrame = { 8, 0 };



};

