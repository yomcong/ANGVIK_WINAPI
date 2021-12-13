#pragma once
#include "Config.h"
#include "GameObject.h"

enum class State { IDLE, JUMP, Fall, SITDOWN, HIT };
enum class Action { IDLE, LEFTMOVE, RIGHTMOVE, ATTACK };

//class PixelCollider;
class Imgae;
class CollisionManager;
class Player : public GameObject
{
public:
	//static enum class Action { IDLE, LeftMove, RightMove, Jump, SitDown, Attack, Hit };
	virtual ~Player() = default;

	virtual HRESULT Init(CollisionManager* collisionManager);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void ChangeAction(Action action);
	void ChangeState(State state);
	void DoAnimation();

	bool FindImage();
	void PosUpdate();

private:
	Image* backArm = nullptr;	// 왼팔
	Image* frontArm = nullptr;	// 오른팔
	Image* body = nullptr;		// 몸통
	Image* head = nullptr;		// 머리

	Image* R_body = nullptr;	// 뛰기(laft)
	Image* R_backArm = nullptr;	// 왼팔
	Image* R_frontArm = nullptr;// 오른팔
	Image* R_head = nullptr;	// 몸통

	// 랜더링 포스
	POINT armPos = {};
	POINT headPos = {};
	POINT bodyPos = {};

	// 캐릭터 애니메이션 프레임 관리
	POINT bodyFrame = { 0, 0 };
	POINT frontArmFrame = { 11, 0 };
	POINT backArmFrame = { 13, 0 };

	// 앉아있을때 카메라 내리기
	bool sitDownCamera = false;

	// 팔 흔들기 변수
	bool b_frontArmMove = true;
	bool b_backArmMove = true;

	// 이동 애니메이션 맥스프레임
	const POINT frontArmMaxFrame = { 15, 2 };
	const POINT backArmMaxFrame = { 15, 2 };
	const POINT bodyMaxFrame = { 11, 1 };

	// 점프력
	float jumpPower = 0.0f;

	// 캐릭터 상태관리
	Action action = Action::IDLE;
	State state = State::IDLE;

	CollisionManager* collisionManager = nullptr;
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

