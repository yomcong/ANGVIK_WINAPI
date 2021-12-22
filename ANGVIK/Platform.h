#pragma once
#include "stdafx.h"
#include "Config.h"
#include "GameObject.h"

class Image;
class Platform : public GameObject
{
public:
	virtual ~Platform() = default;

	virtual HRESULT Init(POINTFLOAT pos, int dir);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	inline void SetIsCollision(bool b_isCollision) { this->b_isCollision = b_isCollision; }

private:
	Image* platform = nullptr;
	Image* R_platform = nullptr;

	float respawnCount = 0.0f;

	const POINT PlatformMaxFrame = { 0, 5 };

	bool b_isCollision = false;

	SubjectTag subTag = SubjectTag::PLATFORM;

};


