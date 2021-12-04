#pragma once
#include "Config.h"
#include "Singleton.h"

class Image;
class MapColliderManager : public Singleton<MapColliderManager>
{
public:
	virtual ~MapColliderManager() = default;

	HRESULT Init();
	void Update();

	bool autoMove(POINTFLOAT pos, RECT shape, float moveSpeed, int bodySize);
	POINTFLOAT Move(POINTFLOAT pos, RECT shape, float moveSpeed, int dir, int bodySize);
	bool checkCollision(RECT shape, int dir, POINT bodySize);

private:
	Image* pixelMap = nullptr;

	// 픽셀 충돌
	COLORREF color = {};
	WORD r, g, b = {};

	//디버그용
	POINTFLOAT pixelPos = {};

};
