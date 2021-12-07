#pragma once
#include "Config.h"
#include "GameObject.h"

enum class State { IDLE, JUMP, Fall, SITDOWN, HIT };
enum class Action { IDLE, LEFTMOVE, RIGHTMOVE, ATTACK };

//class PixelCollider;
class Imgae;
class Player : public GameObject
{
public:
	//static enum class Action { IDLE, LeftMove, RightMove, Jump, SitDown, Attack, Hit };
	virtual ~Player() = default;

	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void ChangeAction(Action action);
	void ChangeState(State state);
	void DoAnimation();

	HRESULT FindImage();
	void PosUpdate();

private:
	Image* backArm = nullptr;	// ����
	Image* frontArm = nullptr;	// ������
	Image* body = nullptr;		// ����
	Image* head = nullptr;		// �Ӹ�

	Image* R_body = nullptr;	// �ٱ�(laft)
	Image* R_backArm = nullptr;	// ����
	Image* R_frontArm = nullptr;// ������
	Image* R_head = nullptr;	// ����

	// ������ ����
	POINT armPos = {};
	POINT headPos = {};
	POINT bodyPos = {};

	// ĳ���� �ִϸ��̼� ������ ����
	POINT bodyFrame = { 0, 0 };
	POINT frontArmFrame = { 11, 0 };
	POINT backArmFrame = { 13, 0 };

	// ĳ���� ����
	direction playerDir = direction::RIGHT;

	// �ɾ������� ī�޶� ������
	bool sitDownCamera = false;

	// �� ���� ����
	bool b_frontArmMove = true;
	bool b_backArmMove = true;

	// �̵� �ִϸ��̼� ����������
	const POINT frontArmStartFrame = { 9, 0 };
	const POINT backArmStartFrame = { 11, 0 };
	const POINT bodyStartFrame = { 0, 0 };
	// �̵� �ִϸ��̼� �ƽ�������
	const POINT frontArmMaxFrame = { 15, 2 };
	const POINT backArmMaxFrame = { 15, 2 };
	const POINT bodyMaxFrame = { 11, 1 };

	// ������
	float jumpPower = 0.0f;

	// ĳ���� ���°���
	Action action = Action::IDLE;
	State state = State::IDLE;

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

