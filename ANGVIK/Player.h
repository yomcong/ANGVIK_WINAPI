#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Subject.h"

enum class State { IDLE, JUMP, FALL, SITDOWN, HIT, ATTACK };

enum class Action { IDLE, LEFTMOVE, RIGHTMOVE, BACKATTACK, FRONTATTACK };

class AmmoManager;
class Imgae;
class Inventory;
class Player : public GameObject, public Subject
{
public:
	virtual ~Player() = default;

	virtual HRESULT Init(AmmoManager* _ammoManager);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	bool FindImage();
	void ChangeAction(Action action);
	void ChangeState(State state);
	void StateCheck();
	void PlayAnimation();
	void PosUpdate();
	void ToStepOn();
	void ToBeHit();
	bool CheckCollision(SubjectTag _subject, RECT _shape, EventTag _eventTag = EventTag::IDLE);
	void AttackHit();
	void Attacking();
	bool EquipItem(ItemType itemType, ItemGrade itemGrade, WeaponType weaponType, bool ChangeItem = false, int dir = 0);
	void ItemDrop(ItemType _itemType, ItemGrade _itemGrade, WeaponType _weaponType = WeaponType::IDLE);
	void TriggerCheck();
	void IsDead();


	inline bool SetIsPlatform(bool b_platform) { return this->b_platform = b_platform; }
	inline bool SetInventoryClose(bool b_inventoryOpen) { return this->b_inventoryOpen = b_inventoryOpen; }
	inline ItemInfo GetItemInfo() { return dropItemInfo; }


private:
	Image* backArm = nullptr;	
	Image* frontArm = nullptr;	
	Image* body = nullptr;		
	Image* head = nullptr;		

	Image* R_backArm = nullptr;	
	Image* R_frontArm = nullptr;
	Image* R_body = nullptr;	
	Image* R_head = nullptr;	

	Image* helmet = nullptr;	
	Image* armor = nullptr;		
	Image* shoes = nullptr;		

	Image* R_helmet = nullptr;	
	Image* R_armor = nullptr;	
	Image* R_shoes = nullptr;	

	Image* backWeapon = nullptr;	
	Image* frontWeapon = nullptr;	

	Image* R_backWeapon = nullptr;	
	Image* R_frontWeapon = nullptr;	

	Image* boneHead = nullptr;		
	Image* boneBody = nullptr;		
	Image* boneEtc = nullptr;		

	// 랜더 포스
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
	bool b_backAttack = false;
	bool b_frontAttack = false;
	float attackCount = false;

	// 중력가속도
	float gAccele = 98.0f;

	// 앉아있을때 카메라 내리기
	bool b_sitDownCamera = false;

	// 팔 앞뒤로 흔들기
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

	const POINT frontArmMaxFrame = { 15, 2 };
	const POINT backArmMaxFrame = { 15, 2 };
	const POINT bodyMaxFrame = { 11, 1 };

	// 트리거 알림 체크
	bool oneTriggerOn = false;
	bool twoTriggerOn = false;

	float jumpingPower = 0.0f;

	// 피격시 무적상태
	float invisibleTime = 0.0f;
	float invisibleCount = 0.0f;
	bool b_invisible = false;

	// 플랫폼 탑승상태
	bool b_platform = false;

	Inventory* playerInventory = nullptr;
	bool b_inventoryOpen = false;
	ItemInfo dropItemInfo = {};

	AmmoManager* ammoManager = nullptr;

	// 캐릭터 상태관리
	Action action = Action::RIGHTMOVE;
	State state = State::IDLE;
	SubjectTag subTag = SubjectTag::PLAYER;

	RECT attackShape = {};

	// 죽었을 때 해골들 물리효과를 위한 충돌렉트
	RECT boneHeadShape = {};
	RECT boneBodyShape = {};
	RECT boneBackArmShape = {};
	RECT boneFrontArmShape = {};

	POINTFLOAT boneHeadPos = {};
	POINTFLOAT boneBodyPos = {};
	POINTFLOAT boneBackArmPos = {};
	POINTFLOAT boneFrontArmPos = {};

	POINT boneBodySize = {};
};

