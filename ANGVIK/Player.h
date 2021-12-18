#pragma once
#include "Config.h"
#include "GameObject.h"

enum class State { IDLE, JUMP, Fall, SITDOWN, HIT, ATTACK};
enum class Action { IDLE, LEFTMOVE, RIGHTMOVE, BACKATTACK, FRONTATTACK};

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
	bool GetItem(ItemType itemType, ItemGrade itemGrade, WeaponType weaponType);
	//bool ChangeItem(ItemType itemType, ItemGrade itemGrade, WeaponType weaponType, Image* equip = nullptr);

	inline bool SetIsPlatform(bool b_platform) { return this->b_platform = b_platform; }


private:
	Image* backArm = nullptr;	// 왼팔
	Image* frontArm = nullptr;	// 오른팔
	Image* body = nullptr;		// 몸통
	Image* head = nullptr;		// 머리

	Image* R_body = nullptr;	// 뛰기(laft)
	Image* R_backArm = nullptr;	// 왼팔
	Image* R_frontArm = nullptr;// 오른팔
	Image* R_head = nullptr;	// 몸통

	Image* helmet = nullptr;	// 헬맷
	Image* armor = nullptr;		// 갑옷
	Image* shoes = nullptr;		// 신발

	Image* R_helmet = nullptr;	// 헬맷
	Image* R_armor = nullptr;	// 갑옷
	Image* R_shoes = nullptr;	// 신발

	Image* backWeapon = nullptr;	// back 무기
	Image* frontWeapon = nullptr;	// front 무기

	Image* R_backWeapon = nullptr;	// back 무기
	Image* R_frontWeapon = nullptr;	// front 무기
	// 랜더링 포스
	POINT frontArmPos = {};
	POINT backArmPos = {};
	POINT headPos = {};
	POINT bodyPos = {};
	POINT backWeaponPos = {};
	POINT frontWeaponPos = {};

	// 캐릭터 애니메이션 프레임 관리
	POINT bodyFrame = { 0, 0 };
	POINT frontArmFrame = { 11, 0 };
	POINT backArmFrame = { 13, 0 };
	POINT frontWeaponFrame = { 0,0 };
	POINT backWeaponFrame = { 0,0 };
	POINT backAttackArmFrame = { 0,0 };
	POINT frontAttackArmFrame = { 0,0 };

	// 공격중
	bool backAttack = false;
	bool frontAttack = false;

	float attackCount = false;


	// 앉아있을때 카메라 내리기
	bool sitDownCamera = false;

	// 팔 흔들기 변수
	bool b_frontArmMove = true;
	bool b_backArmMove = true;

	// 착용 아이템 상태
	ItemType itemType = ItemType::IDLE;
	ItemGrade helmetGrade = ItemGrade::IDLE;
	ItemGrade armorGrade = ItemGrade::IDLE;
	ItemGrade shoesGrade = ItemGrade::IDLE;
	ItemGrade backWeaponGrade = ItemGrade::IDLE;
	ItemGrade frontWeaponGrade = ItemGrade::IDLE;
	WeaponType backWeaponType = WeaponType::IDLE;
	WeaponType frontWeaponType = WeaponType::IDLE;

	bool b_equipArmor = false;
	bool b_equipHelmet = false;
	bool b_equipShoes = false;
	bool b_equipBackWeapon = false;
	bool b_equipFrontWeapon = false;

	// 이동 애니메이션 맥스프레임
	const POINT frontArmMaxFrame = { 15, 2 };
	const POINT backArmMaxFrame = { 15, 2 };
	const POINT bodyMaxFrame = { 11, 1 };

	// 점프력
	float jumpPower = 0.0f;
	float invisibleTime = 0.0f;
	float invisibleCount = 0.0f;
	bool b_invisible = false;
	bool b_platform = false;




	// 캐릭터 상태관리
	Action action = Action::IDLE;
	State state = State::IDLE;
	SubjectTag subTag = SubjectTag::PLAYER;

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

