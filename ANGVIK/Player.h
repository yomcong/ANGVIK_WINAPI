#pragma once
#include "Config.h"
#include "GameObject.h"

enum class State { Idel, JUMP, Fall, SITDOWN };
enum class Action { Idle, LEFTMOVE, RIGHTMOVE, ATTACK, HIT };

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

	void ChangeAction(Action action);
	void DoAnimation();

private:
	Image* backArm = nullptr;	// ����
	Image* frontArm = nullptr;	// ������
	Image* body = nullptr;		// ����
	Image* head = nullptr;		// �Ӹ�

	// ĳ���� �ִϸ��̼� ������ ����
	POINT bodyFrame = { 0, 0 };
	POINT frontArmFrame = { 11, 0 };
	POINT backArmFrame = { 13, 0 };

	// �� ���� ����
	bool b_frontArmMove = true;
	bool b_backArmMove = true;

	// �ִϸ��̼� ����������
	const POINT backArmStartFrame = { 9, 0 };
	const POINT frontArmStartFrame = { 9, 0 };
	const POINT bodyStartFrame = { 0, 0 };
	// �ִϸ��̼� �ƽ�������
	const POINT backArmMaxFrame = { 15, 2 };
	const POINT frontArmMaxFrame = { 15, 2 };
	const POINT bodyMaxFrame = { 12, 1 };


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

	// �̹��� ������ (��ü����)
	POINT DBarmPos = { 0, 0 };
	POINT DBbodyPos = { 0, 0 };



};

