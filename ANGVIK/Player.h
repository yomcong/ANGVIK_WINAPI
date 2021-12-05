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
	Image* backArm = nullptr;	// 왼팔
	Image* frontArm = nullptr;	// 오른팔
	Image* body = nullptr;		// 몸통
	Image* head = nullptr;		// 머리

	// 캐릭터 애니메이션 프레임 관리
	POINT bodyFrame = { 0, 0 };
	POINT frontArmFrame = { 11, 0 };
	POINT backArmFrame = { 13, 0 };

	// 팔 흔들기 변수
	bool b_frontArmMove = true;
	bool b_backArmMove = true;

	// 애니메이션 시작프레임
	const POINT backArmStartFrame = { 9, 0 };
	const POINT frontArmStartFrame = { 9, 0 };
	const POINT bodyStartFrame = { 0, 0 };
	// 애니메이션 맥스프레임
	const POINT backArmMaxFrame = { 15, 2 };
	const POINT frontArmMaxFrame = { 15, 2 };
	const POINT bodyMaxFrame = { 12, 1 };


	// 점프력
	float jumpPower = 0.0f;

	// 캐릭터 상태관리
	Action action = Action::Idle;
	State state = State::Idel;

	// 디버그용
	Image* DBbackArm = nullptr;
	Image* DBfrontArm = nullptr;
	Image* DBbody = nullptr;
	Image* DBhead0 = nullptr;
	Image* DBhead1 = nullptr;
	Image* DBhead2 = nullptr;
	Image* DBhead3 = nullptr;
	Image* DBgoldBody = nullptr;
	Image* DBgoldFoot = nullptr;

	// 이미지 디버깅용 (인체실험)
	POINT DBarmPos = { 0, 0 };
	POINT DBbodyPos = { 0, 0 };



};

