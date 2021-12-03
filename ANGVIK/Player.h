#pragma once
#include "Config.h"
#include "GameObject.h"


//class PixelCollider;
class Imgae;
class Player : public GameObject
{
public:
	//static enum class Action { Idle, LeftMove, RightMove, Jump, SitDown, Attack, Hit };
	virtual ~Player() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

private:
	enum class State { Idel, JUMP,Fall, SITDOWN };
	enum class Action { Idle, LEFTMOVE, RIGHTMOVE, ATTACK, HIT };


	Image* backArm = nullptr;	// ����
	Image* frontArm = nullptr;	// ������
	Image* body = nullptr;		// ����
	Image* head = nullptr;		// �Ӹ�

	// ĳ���� �ٵ������� ����
	POINT bodyFrame = { 0, 0 };
	POINT frontArmFrame = { 11, 0 };
	POINT backArmFrame = { 13, 0 };
	POINT bodySize = { 0, 0 };

	// ���� ��ǥ
	POINTFLOAT renderPos = { 0, 0 };

	// �� ���� ���� ����
	bool b_frontArmMove = true;
	bool b_backArmMove = true;

	// ������ ����
	float frameCount = 0.0f;
	
	// ������
	float jumpPower = 0.0f;

	// ĳ���� ���°���
	Action action = Action::Idle;
	State state = State::Idel;

	// ����׿�
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

