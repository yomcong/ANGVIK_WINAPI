#pragma once
#include "Config.h"
#include "GameObject.h"

enum class PlayerAction { NORMAL, MOVE, JUMP, ATTACK, HIT };

class PixelCollider;
class Imgae;
class Player : public GameObject
{
public:
	virtual ~Player() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();


private:
	Image* backArm = nullptr;
	Image* frontArm = nullptr;
	Image* body = nullptr;

	POINT bodyFrame = { 0, 0 };
	POINT frontArmFrame = { 11, 0 };
	POINT backArmFrame = { 13, 0 };

	bool frontArmMove = true;
	bool backArmMove = true;


	int frameCount = 0;

	

	int bodySize_X = 0;
	int bodySize_Y = 0;

	PlayerAction action = PlayerAction::NORMAL;

	PixelCollider* playerPixelCollision = nullptr;


	//디버그용
	Image* DBbackArm = nullptr;
	Image* DBfrontArm = nullptr;
	Image* DBbody = nullptr;
	Image* DBhead0 = nullptr;
	Image* DBhead1 = nullptr;
	Image* DBhead2 = nullptr;
	Image* DBhead3 = nullptr;
	Image* DBgoldBody = nullptr;
	Image* DBgoldFoot = nullptr;

	// 이미지 디버깅용
	POINT DBarmPos = { 0, 0 };
	POINT DBbodyPos = { 0, 0 };

	bool DBplayerRect = false;
	//


	// 픽셀 충돌
	//COLORREF color = {};
	//WORD r, g, b = {};


};

