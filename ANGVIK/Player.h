#pragma once
#include "Config.h"
#include "GameObject.h"

enum class PlayerAction { NORMAL, LEFTMOVE, RIGHTMOVE, JUMP, SITDOWN, ATTACK, HIT };

//class PixelCollider;
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
	Image* backArm = nullptr;	// ����
	Image* frontArm = nullptr;	// ������
	Image* body = nullptr;		// ����

	// ĳ���� �ٵ������� ����
	POINT bodyFrame = { 0, 0 };
	POINT frontArmFrame = { 11, 0 };
	POINT backArmFrame = { 13, 0 };
	POINT bodySize = { 0, 0 };

	// �� ���� ���� ����
	bool b_frontArmMove = true;
	bool b_backArmMove = true;

	// ������ ����
	float frameCount = 0.0f;

	// ĳ���� ������
	/*int bodySize_X = 0;
	int bodySize_Y = 0;*/

	// ĳ���� ���°���
	PlayerAction action = PlayerAction::NORMAL;

	// �ȼ� �浹
	//PixelCollider* playerPixelCollision = nullptr;


	//����׿�
	Image* DBbackArm = nullptr;
	Image* DBfrontArm = nullptr;
	Image* DBbody = nullptr;
	Image* DBhead0 = nullptr;
	Image* DBhead1 = nullptr;
	Image* DBhead2 = nullptr;
	Image* DBhead3 = nullptr;
	Image* DBgoldBody = nullptr;
	Image* DBgoldFoot = nullptr;

	// �̹��� ������
	POINT DBarmPos = { 0, 0 };
	POINT DBbodyPos = { 0, 0 };

	bool DBplayerRect = false;
	

};

