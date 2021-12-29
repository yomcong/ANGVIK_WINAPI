#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Subject.h"

class Image;
class Platform : public GameObject, public Subject
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

	bool b_windowIn = false;


};


