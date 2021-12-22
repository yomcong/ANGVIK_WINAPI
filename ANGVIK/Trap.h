#pragma once
#include "stdafx.h"
#include "Config.h"
#include "GameObject.h"

class Trap : public GameObject
{
public:
	virtual ~Trap() = default;

	virtual HRESULT Init(POINTFLOAT pos, POINT bodySize);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();


private:



};

