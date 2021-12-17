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
	void PosUpdate();
	void ToStepOn();
	void ToBeHit();
	bool CheckCollision(SubjectTag subject, RECT shape);
	bool FindImage();
	void GetItem(ItemType itemType, ItemGrade itemGrade);

	inline bool SetIsPlatform(bool b_platform) { return this->b_platform = b_platform; }


private:
	Image* backArm = nullptr;	// ����
	Image* frontArm = nullptr;	// ������
	Image* body = nullptr;		// ����
	Image* head = nullptr;		// �Ӹ�

	Image* R_body = nullptr;	// �ٱ�(laft)
	Image* R_backArm = nullptr;	// ����
	Image* R_frontArm = nullptr;// ������
	Image* R_head = nullptr;	// ����

	Image* goldArmor = nullptr;	// Ȳ�� ����
	Image* goldShoes = nullptr; // Ȳ�� �Ź�

	Image* R_goldArmor = nullptr;	// Ȳ�� ����
	Image* R_goldShoes = nullptr; // Ȳ�� �Ź�
	// ������ ����
	POINT frontArmPos = {};
	POINT backArmPos = {};
	POINT headPos = {};
	POINT bodyPos = {};

	// ĳ���� �ִϸ��̼� ������ ����
	POINT bodyFrame = { 0, 0 };
	POINT frontArmFrame = { 11, 0 };
	POINT backArmFrame = { 13, 0 };

	// �ɾ������� ī�޶� ������
	bool sitDownCamera = false;

	// �� ���� ����
	bool b_frontArmMove = true;
	bool b_backArmMove = true;

	// �̵� �ִϸ��̼� �ƽ�������
	const POINT frontArmMaxFrame = { 15, 2 };
	const POINT backArmMaxFrame = { 15, 2 };
	const POINT bodyMaxFrame = { 11, 1 };

	// ������
	float jumpPower = 0.0f;
	float invisibleTime = 0.0f;
	float invisibleCount = 0.0f;
	bool b_invisible = false;
	bool b_platform = false;
	
	bool b_equipArmor = false;
	bool b_equipHelmet = false;
	bool b_equipShoes = false;
	bool b_equipLeftWeapon = false;
	bool b_equipRightWeapon = false;


	// ĳ���� ���°���
	Action action = Action::IDLE;
	State state = State::IDLE;
	SubjectTag subTag = SubjectTag::PLAYER;

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

