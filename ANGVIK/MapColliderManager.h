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

	bool AutoFall(POINTFLOAT pos, RECT shape, float moveSpeed, POINT bodySize);
	POINTFLOAT Move(POINTFLOAT pos, RECT shape, float moveSpeed, int dir, POINT bodySize);
	bool Jump(POINTFLOAT pos, RECT shape, float moveSpeed, POINT bodySize);
	bool checkCollision(RECT shape, int dir, POINT bodySize);
	//bool AutoMove(POINTFLOAT pos, RECT shape, float moveSpeed, int dir, POINT bodySize);

private:
	Image* pixelMap = nullptr;

	// �ȼ� �浹
	COLORREF color = {};
	WORD r, g, b = {};


};
