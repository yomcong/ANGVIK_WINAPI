#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Subject.h"

class Trap : public GameObject, public Subject
{
public:
	virtual ~Trap() = default;

	virtual HRESULT Init(POINTFLOAT pos, POINT bodySize);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

private:
	bool b_windowIn = false;

	SubjectTag subTag = SubjectTag::TRAP;

};

