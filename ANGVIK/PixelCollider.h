#pragma once
#include "Config.h"
#include "GameEntity.h"

// RGB ¸â¹öº¯¼ö Áú¹®

class Image;
class PixelCollider : public GameEntity
{
public:
	virtual ~PixelCollider() = default;

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	float autoMove(float x, float y, RECT shape, float moveSpeed);
	POINTFLOAT Move(POINTFLOAT pos, RECT shape, float moveSpeed, int dir, int bodySize);

private:
	Image* pixelMap = nullptr;

	// ÇÈ¼¿ Ãæµ¹
	COLORREF color = {};
	WORD r, g, b = {};

};

